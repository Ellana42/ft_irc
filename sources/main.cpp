#include "Password.hpp"
#include "test.hpp"
#include "ft_irc.hpp"
#include "Application.hpp"

int main( int ac, char **av )
{
	if ( ac != 3 )
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return ( 1 );
	}
	try
	{
		int port = atoi( av[1] );
		std::string password = std::string( av[2] );

		Application app( port, password );
		app.launch_server();
	}
	catch ( std::exception & e )
	{
		log_event::error( e.what() );
		return ( 1 );
	}
	return ( 0 );
}
