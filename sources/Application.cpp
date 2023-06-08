#include "Application.hpp"
#include "ft_irc.hpp"
#include "Password.hpp"
#include <exception>
#include <stdexcept>

#define RPL_WELCOME "001"

std::string const welcome()
{
	std::string reply = "127.0.0.1 ";
	reply += RPL_WELCOME " ";
	reply += "alice";
	reply += " :Welcome to the Internet Relay Network ";
	reply += "alice!alice@alicehost";
	reply += "\r\n";
	return reply;
}

Application::Application( int port, std::string password ): port( port )
{
	passwords = new Password( password );
	context = new Context( *passwords );

	std::cout << "Creating server socket..." << std::endl;
	server.fd = socket( AF_INET, SOCK_STREAM, 0 );

	if ( server.fd == -1 )
	{
		std::cerr << "Can't create a socket!";
		throw std::runtime_error( "Can't create a socket!" );
	}

	server.info.sin_family = AF_INET;
	if ( port < 6660 || port > 7000 )
	{
		throw ( std::runtime_error( "Invalid port: port must be between 6660 and 7000" ));
	}
	server.info.sin_port = htons( port );
	server.info.sin_addr.s_addr = htonl( INADDR_ANY );

	std::cout << "Binding socket to sockaddr..." << std::endl;
	if ( bind( server.fd, ( struct sockaddr * ) &server.info,
				sizeof( server.info ) ) == -1 )
	{
		throw ( std::runtime_error( "Can't connect to port: Port might be in use." ));
	}
	/* while ( bind( server.fd, ( struct sockaddr * ) &server.info, */
	/*               sizeof( server.info ) ) == -1 ) */
	/* { */
	/* 	/1* std::cerr << "Can't bind to IP/port " << port << " - Trying next port." << *1/ */
	/* 	/1* std::endl; *1/ */
	/* 	port++; */
	/* 	server.info.sin_port = htons( port ); */
	/* 	/1* throw std::runtime_error( "Can't bind to IP/port" ); *1/ */
	/* } */
	std::cout << "Connected to port " << port << std::endl;
	std::cout << "Mark the socket for listening..." << std::endl;
	if ( listen( server.fd, SOMAXCONN ) == -1 )
	{
		std::cerr << "Can't listen !";
		throw std::runtime_error( "Can't listen !" );
	}
}

void Application::launch_server()
{
	std::vector<pollfd> client_fds( max_clients + 1 );
	client_fds[0].fd = server.fd;
	client_fds[0].events = POLLIN;

	int num_clients = 0;  // keep track of number of connected clients

	while ( true )
	{
		int num_ready = poll( client_fds.data(), num_clients + 1, -1 );
		if ( num_ready == -1 )
		{
			std::cerr << "Error in poll()";
			throw std::runtime_error( "Error in poll()" );
		}

		if ( client_fds[0].revents & POLLIN )
		{
			socklen_t clientSize = sizeof( clients.info );

			std::cout << "Accept client call..." << std::endl;
			clients.fd = accept( server.fd, ( struct sockaddr * ) &clients.info,
			                     &clientSize );

			std::cout << "Received call..." << std::endl;
			if ( clients.fd == -1 )
			{
				std::cerr << "Problem with client connecting!";
				throw std::runtime_error( "Problem with client connecting!" );
			}

			// add new client to the list of file descriptors to monitor
			if ( num_clients == max_clients )
			{
				std::cerr << "Too many clients!";
				throw std::runtime_error( "Too many clients!" );
			}
			client_fds[num_clients + 1].fd = clients.fd;
			client_fds[num_clients + 1].events = POLLIN;

			// Creating new user for client
			context->create_unregistered_user( clients.fd );

			num_clients++;
		}
		int i = 1;
		while ( i <= num_clients )
		{
			if ( client_fds[i].fd != -1 && client_fds[i].revents & POLLIN )
			{
				read_message( client_fds[i].fd, &num_clients );
			}
			i++;
		}
	}
	close( server.fd );
}

void Application::read_message( int fd, int *num_clients )
{
	char buf[4096];
	memset( buf, 0, sizeof( buf ) );
	size_t terminator = std::string::npos;
	int bytes_recv = 0;

	std::string message_buffer;
	while ( terminator == std::string::npos )
	{
		bytes_recv = recv( fd, buf, sizeof( buf ), 0 );
		/* std::cerr << "- BUFFER contains: [" << buf << "]" << std::endl; */
		if ( bytes_recv == -1 )
		{
			std::cerr << "There was a connection issue." << std::endl;
			break;
		}
		if ( bytes_recv == 0 )
		{
			std::cout << "The client disconnected" << std::endl;
			close( fd );
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


			// TODO : check for incomplete messages / read until \r\n
			std::cout << "Command : [";
			examineString( first_command );
			std::cout << "]" << std::endl;
			context->handle_message( context->get_user_by_socket( fd ),
			                         first_command );

			pos = terminator + 2;
			terminator = message_buffer.find( "\r\n", pos );
		}
	}
}

Application::~Application()
{
	delete passwords;
	delete context;
}
