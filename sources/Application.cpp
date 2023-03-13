#include "../includes/Application.hpp"
#include <stdexcept>

void *handle_client( void *arg )
{
	int client_socket = *( ( int * ) arg );
	char buf[4096];
	while ( true )
	{
		// clear buffer
		memset( buf, 0, 4096 );

		// wait for a message
		int bytes_recv = recv( client_socket, buf, 4096, 0 );
		if ( bytes_recv == -1 )
		{
			std::cerr << "There was a connection issue." << std::endl;
		}
		if ( bytes_recv == 0 )
		{
			std::cout << "The client disconnected" << std::endl;
			break;
		}

		// display message
		std::cout << "Received: " << std::string( buf, 0, bytes_recv );

		// return message
		std::string response =
		    "001    RPL_WELCOME Welcome to the Internet Relay Network <nick>!<user>@<host>";
		response = "CAP";
		send( client_socket, response.c_str(), response.length() + 1, 0 );
	}
	// close socket
	close( client_socket );
	return ( NULL );
}

Application::Application()
{
	// TODO create context

	std::cout << "Creating server socket..." << std::endl;
	server.fd = socket( AF_INET, SOCK_STREAM, 0 );

	if ( server.fd == -1 )
	{
		std::cerr << "Can't create a socket!";
		throw std::runtime_error( "Can't create a socket!" );
	}

	server.info.sin_family = AF_INET;
	server.info.sin_port = htons( 6667 ); // TODO test other ports ?
	server.info.sin_addr.s_addr = htonl( INADDR_ANY );

	std::cout << "Binding socket to sockaddr..." << std::endl;
	if ( bind( server.fd, ( struct sockaddr * ) & server.info,
	           sizeof( server.info ) ) == -1 )
	{
		std::cerr << "Can't bind to IP/port";

		throw std::runtime_error( "Can't bind to IP/port" );
	}
	std::cout << "Mark the socket for listening..." << std::endl;
	if ( listen( server.fd, SOMAXCONN ) == -1 )
	{
		std::cerr << "Can't listen !";
		throw std::runtime_error( "Can't listen !" );
	}

}

void Application::launch_server( void )
{
	while ( true )
	{
		socklen_t clientSize = sizeof( clients );

		std::cout << "Accept client call..." << std::endl;
		clients.fd = accept( server.fd, ( struct sockaddr * ) & clients.info,
		                     &clientSize );

		std::cout << "Received call..." << std::endl;
		if ( clients.fd == -1 )
		{
			std::cerr << "Problem with client connecting!";
			throw std::runtime_error( "Problem with client connecting!" );
		}

		pthread_t newThread; // create new thread to handle client
		if ( pthread_create( &newThread, NULL, handle_client,
		                     ( void * )&clients.fd ) != 0 )
		{
			std::cerr << "Failed to create thread";
			throw std::runtime_error( "Failed to create thread" );
		}
		threads.push_back( newThread );
	}
}

Application::~Application() {}

