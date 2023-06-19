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

Application::Application( int port, std::string password ) : port( port )
{
	passwords = new Password( password );
	context = new Context( *passwords );

	log_event::info( "Application: Creating server socket..." );
	server.fd = socket( AF_INET, SOCK_STREAM, 0 );

	if ( server.fd == -1 )
	{
		throw std::runtime_error( "Application: Can't create a socket!" );
	}

	// Set the server socket to non-blocking
	int flags = fcntl( server.fd, F_GETFL, 0 );
	fcntl( server.fd, F_SETFL, flags | O_NONBLOCK );

	server.info.sin_family = AF_INET;
	if ( port < 6660 || port > 7000 )
	{
		throw ( std::runtime_error( "Application: Invalid port: port must be between 6660 and 7000" ) );
	}
	server.info.sin_port = htons( port );
	server.info.sin_addr.s_addr = htonl( INADDR_ANY );

	log_event::info( "Application: Binding socket to sockaddr..." );
	if ( bind( server.fd, ( struct sockaddr * )&server.info, sizeof( server.info ) ) == -1 )
	{
		throw ( std::runtime_error( "Application: Can't bind port: Port might be in use." ) );
	}
	log_event::info( "Application: Connected to port", port );
	log_event::info( "Application: Mark the socket for listening..." );
	if ( listen( server.fd, SOMAXCONN ) == -1 )
	{
		throw std::runtime_error( "Application: Can't listen !" );
	}
}

void Application::launch_server()
{
	std::vector<pollfd> client_fds( max_clients + 1 );
	client_fds[0].fd = server.fd;
	client_fds[0].events = POLLIN;

	int num_clients = 0; // keep track of number of connected clients
	log_event::info( "Application: Launching server..." );
	signal( SIGINT, sig::signalHandler );

	while ( sig::stopServer == false )
	{
		int num_ready = poll( client_fds.data(), num_clients + 1, -1 );
		if ( num_ready == -1 && sig::stopServer == true )
		{
			log_event::warn( "Application: Poll error because of intercepted signal" );
			break ;
		}
		else if ( num_ready == -1 && sig::stopServer == true )
		{
			throw std::runtime_error( "Application: Poll error" );
		}

		if ( client_fds[0].revents & POLLIN )
		{
			socklen_t clientSize = sizeof( clients.info );

			log_event::info( "Application: Accepting client call..." );
			clients.fd = accept( server.fd, ( struct sockaddr * )&clients.info,
								&clientSize );

			log_event::info( "Application: Received client call..." );
			if ( clients.fd == -1 )
			{
				throw std::runtime_error( "Application: Client cannot connect!" );
			}

			// Set the client socket to non-blocking
			int flags = fcntl( clients.fd, F_GETFL, 0 );
			fcntl( clients.fd, F_SETFL, flags | O_NONBLOCK );

			// add new client to the list of file descriptors to monitor
			if ( num_clients == max_clients )
			{
				throw std::runtime_error( "Application: Too many clients!" );
			}
			client_fds[num_clients + 1].fd = clients.fd;
			client_fds[num_clients + 1].events = POLLIN;

			// Creating new user for client
			context->create_unregistered_user( clients.fd );
			num_clients++;
		}
		int i = 1;
		while ( i <= num_clients && sig::stopServer == false )
		{
			if ( client_fds[i].fd != -1 && client_fds[i].revents & POLLIN )
			{
				read_message( client_fds[i].fd, &num_clients );
			}
			i++;
		}
	}
	log_event::info( "Application: Terminating server loop" );
	close( server.fd );
}

void Application::read_message( int fd, int *num_clients )
{
	char buf[4096];
	memset( buf, 0, sizeof( buf ) );
	size_t terminator = std::string::npos;
	int bytes_recv = 0;

	std::string message_buffer;
	while ( terminator == std::string::npos && sig::stopServer == false)
	{
		bytes_recv = recv( fd, buf, sizeof( buf ), 0 );
		if ( bytes_recv == -1 )
		{
			if ( errno == EWOULDBLOCK || errno == EAGAIN )
			{
				// No more data to read, exit the loop
				break;
			}
			else
			{
				log_event::warn( "Application: Connection issue while receiving message from socket", fd );
				break;
			}
		}
		if ( bytes_recv == 0 )
		{
			log_event::info( "Application: Client disconnected from socket", fd );
			context->remove_user( fd );
			/* close( fd ); */
			fd = -1;
			( *num_clients )--;
			break;
		}
		message_buffer += std::string( buf );
		terminator = message_buffer.find( "\r\n", 0 );
	}
	if ( terminator != std::string::npos )
	{
		size_t pos = 0;
		while ( terminator != std::string::npos )
		{
			std::string first_command = message_buffer.substr( pos, terminator + 2 - pos );

			log_event::command( fd, first_command );
			context->handle_message( context->get_user_by_socket( fd ),
									first_command );

			pos = terminator + 2;
			terminator = message_buffer.find( "\r\n", pos );
		}
	}
}

Application::~Application()
{
	log_event::info( "Application: Terminating application" );
	log_event::info( "Application: stopServer var = ", sig::stopServer );
	delete passwords;
	delete context;
}

