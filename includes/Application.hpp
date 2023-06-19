#ifndef APPLICATION_H
#define APPLICATION_H

#include "Password.hpp"
#include "ft_irc.hpp"

#include "Context.hpp"

struct s_socket
{
	int fd;
	struct sockaddr_in info;
};

class Application
{
	private:
		int	port;
		s_socket server;
		s_socket clients;

		std::list<pthread_t> threads;
		const static int max_clients = SOMAXCONN;
		int num_connections;
		
		std::vector<pollfd> * poll_fds;

		Password * passwords;
		Context * context;

		void initialize_server( void );
		void wait_for_socket_event( void );
		void connect_new_client( void );
		void read_message( int fd );

		class StopServerException : public std::exception {};

	public:
		Application( int port, std::string password );
		Application( const Application & src );
		Application & operator=( const Application & rhs );
		virtual ~Application();

		void client_timeout_check( void ); // Separate class
		void launch_server( void );
};

#endif /* APPLICATION_H */
