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
		Password * passwords;
		Context * context;

		s_socket server;
		s_socket clients;

		std::list<pthread_t> threads;
		const static int max_clients = SOMAXCONN;
		void read_message(int fd, int *num_clients);

	public:
		Application( int port, std::string password );
		Application( const Application & src );
		Application & operator=( const Application & rhs );
		virtual ~Application();

		void client_timeout_check( void ); // Separate class
		/* void listen( void ); // transmit to context ? */
		void launch_server( void );
};

#endif /* APPLICATION_H */
