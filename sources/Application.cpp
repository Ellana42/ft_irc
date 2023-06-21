#include "Application.hpp"
#include "ft_irc.hpp"
#include "Password.hpp"
#include "log_event.hpp"
#include "signal.hpp"
#include <csignal>
#include <exception>
#include <stdexcept>
#include <fcntl.h> // Include for fcntl function
#include <errno.h>
#include <sys/poll.h>
#include <vector>

Application::Application(int port, std::string password) : port(port) {
  initialize_server();
  passwords = new Password(password);
  context = new Context(*this, *passwords);
}

Application::~Application() {
  log_event::info("Application: Terminating application");
  close(server.fd);
  delete passwords;
  delete context;
  delete poll_fds;
}

void Application::initialize_server(void) {
  log_event::info("Application: Initializing server...");
  log_event::info("Application: Creating server socket...");
  server.fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server.fd == -1) {
    throw std::runtime_error("Application: Can't create a socket!");
  }
  log_event::info("Application: Setting the server socket to non-blocking...");
  int flags = fcntl(server.fd, F_GETFL, 0);
  fcntl(server.fd, F_SETFL, flags | O_NONBLOCK);

  log_event::info("Application: Connecting to port", port);
  server.info.sin_family = AF_INET;
  if (port < 6660 || port > 7000) {
    throw(std::runtime_error("Application: Invalid port: port must be between 6660 and 7000"));
  }
  server.info.sin_port = htons(port);
  server.info.sin_addr.s_addr = htonl(INADDR_ANY);

  log_event::info("Application: Binding socket...");
  if (bind(server.fd, (struct sockaddr *)&server.info, sizeof(server.info)) == -1) {
    throw(std::runtime_error("Application: Can't bind port: Port might be in use."));
  }
  log_event::info("Application: Mark the socket for listening...");
  if (listen(server.fd, SOMAXCONN) == -1) {
    throw std::runtime_error("Application: Can't listen !");
  }
  poll_fds = new std::vector<pollfd>(max_clients + 1);
  signal(SIGINT, sig::signalHandler);
  log_event::info("Application: Server initialized.");
}

void Application::launch_server(void) {
  std::vector<pollfd> &client_fds = *poll_fds;
  client_fds[0].fd = server.fd;
  client_fds[0].events = POLLIN;

  num_connections = 0; // keep track of number of connected clients
  log_event::info("Application: Launching server...");

  while (sig::stopServer == false) {
    try {
      wait_for_socket_event();
      connect_new_client();
      read_client_sockets();
      send_queued_messages();
    } catch (Application::StopServerException &e) {
      log_event::warn("Application: Stopping server");
      break;
    }
  }
  log_event::info("Application: Terminating server loop");
}

void Application::read_client_sockets(void) {
  std::vector<pollfd> &client_fds = *poll_fds;
  for (int i = 1; i <= num_connections && sig::stopServer == false; i++) {
    if (client_fds[i].fd != -1 && client_fds[i].revents & POLLIN) {
      read_message(client_fds[i].fd);
    }
  }
}

void Application::wait_for_socket_event(void) {
  std::vector<pollfd> &client_fds = *poll_fds;
  int num_ready = poll(client_fds.data(), num_connections + 1, -1);
  if (num_ready == -1 && sig::stopServer == true) {
    log_event::warn("Application: Poll error because of intercepted signal");
    throw Application::StopServerException();
  } else if (num_ready == -1 && sig::stopServer == true) {
    throw std::runtime_error("Application: Poll error");
  }
}

void Application::connect_new_client(void) {
  std::vector<pollfd> &client_fds = *poll_fds;
  if (!(client_fds[0].revents & POLLIN)) {
    return;
  }
  socklen_t clientSize = sizeof(clients.info);

  log_event::info("Application: Accepting client call...");
  clients.fd = accept(server.fd, (struct sockaddr *)&clients.info, &clientSize);

  log_event::info("Application: Received client call...");
  if (clients.fd == -1) {
    throw std::runtime_error("Application: Client cannot connect!");
  }

  // Set the client socket to non-blocking
  int flags = fcntl(clients.fd, F_GETFL, 0);
  fcntl(clients.fd, F_SETFL, flags | O_NONBLOCK);

  // add new client to the list of file descriptors to monitor
  if (num_connections == max_clients) {
    throw std::runtime_error("Application: Too many clients!");
  }
  client_fds[num_connections + 1].fd = clients.fd;
  client_fds[num_connections + 1].events = POLLIN | POLLOUT;

  // Creating new user for client
  context->create_unregistered_user(clients.fd);
  num_connections++;
}

void Application::disconnect_client(int fd) {
  log_event::info("Application: Client disconnected from socket", fd);
  context->remove_user(fd);
  fd = -1;
  num_connections--;
}

void Application::read_message(int fd) {
  char buf[4096];
  memset(buf, 0, sizeof(buf));
  size_t terminator = std::string::npos;
  int bytes_recv = 0;

  std::string message_buffer;
  while (terminator == std::string::npos && sig::stopServer == false) {
    bytes_recv = recv(fd, buf, sizeof(buf), 0);
    if (bytes_recv == -1) {
      if (errno == EWOULDBLOCK || errno == EAGAIN) {
        // No more data to read, exit the loop
        break;
      } else {
        log_event::warn("Application: Connection issue while receiving message from socket", fd);
        disconnect_client(fd);
        break;
      }
    }
    if (bytes_recv == 0) {
      disconnect_client(fd);
      break;
    }
    message_buffer += std::string(buf);
    terminator = message_buffer.find("\r\n", 0);
  }
  if (terminator != std::string::npos) {
    size_t pos = 0;
    while (terminator != std::string::npos) {
      std::string first_command = message_buffer.substr(pos, terminator + 2 - pos);

      log_event::command(fd, first_command);
      context->handle_message(context->get_user_by_socket(fd), first_command);

      pos = terminator + 2;
      terminator = message_buffer.find("\r\n", pos);
    }
  }
}

void Application::send_message(int socket, const std::string& message) {
  Message1 newMessage;
  newMessage.socket = socket;
  newMessage.message = message;
  log_event::info("Application: saving message to send:", message);
  message_list.push_back(newMessage);
}

void Application::send_queued_messages() {
  std::vector<pollfd> &client_fds = *poll_fds;

  for (std::vector<Message1>::const_iterator it = message_list.begin(); it != message_list.end(); ++it) {
    const Message1& message = *it;
    int index = -1;
    for (int i = 1; i <= num_connections; i++) {
      if (client_fds[i].fd == message.socket) {
        index = i;
        break;
      }
    }

    if (index != -1 && client_fds[index].revents & POLLOUT) {
      log_event::info("MESSAGE:", message.message.c_str());
      ssize_t bytes_sent = send(message.socket, message.message.c_str(), message.message.length(), 0);
      if (bytes_sent == -1) {
        log_event::warn("Application: Error while sending message to socket", message.socket);
        disconnect_client(message.socket);
      }
    }
  }

  message_list.clear();
}
