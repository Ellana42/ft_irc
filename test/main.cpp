#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

# define RPL_WELCOME "001"

std::string const welcome( void )
{
	std::string reply = "127.0.0.1 ";
	reply += RPL_WELCOME " ";
	reply += "alice";
	reply += " :Welcome to the Internet Relay Network ";
	reply += "alice!alice@alicehost";
	reply += "\r\n";
	return ( reply );
}

int	main( void )
{
	// main.cpp
	std::cout << "Creating server socket..." << std::endl;
	int listening = socket( AF_INET, SOCK_STREAM, 0 );
	struct sockaddr_in hint;

	if ( listening == -1 )
	{
		std::cerr << "Can't create a socket!";
		return -1;
	}

	hint.sin_family = AF_INET;
	hint.sin_port = htons( 6667 );
	hint.sin_addr.s_addr = inet_addr( "127.0.0.1" );

	std::cout << "Binding socket to sockaddr..." << std::endl;
	if ( bind( listening, ( struct sockaddr * )&hint, sizeof( hint ) ) == -1 )
	{
		std::cerr << "Can't bind to IP/port";
		return -2;
	}
	std::cout << "Mark the socket for listening..." << std::endl;
	if ( listen( listening, SOMAXCONN ) == -1 )
	{
		std::cerr << "Can't listen !";
		return -3;
	}
	sockaddr_in client;
	socklen_t clientSize = sizeof( client );

	std::cout << "Accept client call..." << std::endl;
	int clientSocket = accept( listening, ( struct sockaddr * )&client,
	                           &clientSize );

	std::cout << "Received call..." << std::endl;
	if ( clientSocket == -1 )
	{
		std::cerr << "Problem with client connecting!";
		return -4;
	}
	// main.cpp
	char buf[4096];
	while ( true )
	{
		// clear buffer
		memset( buf, 0, 4096 );

		// wait for a message
		int bytesRecv = recv( clientSocket, buf, 4096, 0 );
		if ( bytesRecv == -1 )
		{
			std::cerr << "There was a connection issue." << std::endl;
		}
		if ( bytesRecv == 0 )
		{
			std::cout << "The client disconnected" << std::endl;
		}

		// display message
		std::cout << "Received: " << std::string( buf, 0, bytesRecv );

		// return message
		std::string response = welcome();
		/* "001    RPL_WELCOME Welcome to the Internet Relay Network <nick>!<user>@<host>"; */
		/* response = "CAP"; */
		send( clientSocket, response.c_str(), response.length() + 1, 0 );
	}
	// close socket
	close( clientSocket );
}
