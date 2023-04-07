#ifndef APPLICATION_H
#define APPLICATION_H

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
		Context * context;

		s_socket server;
		s_socket clients;

		std::list<pthread_t> threads;
		const static int max_clients = SOMAXCONN;

	public:
		Application();
		Application( const Application & src );
		Application & operator=( const Application & rhs );
		virtual ~Application();

		void client_timeout_check( void ); // Separate class
		/* void listen( void ); // transmit to context ? */
		void launch_server( void );
};

#endif /* APPLICATION_H */
