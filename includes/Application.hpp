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

struct Message1 {
  int socket;
  std::string message;
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
		std::vector<Message1> message_list;

		Password * passwords;
		Context * context;

		void initialize_server( void );
		void wait_for_socket_event( void );
		void connect_new_client( void );
		void read_client_sockets( void );
		void read_message( int fd );
		void get_commands_from_socket( int fd, std::string & message_buffer );
		bool buffer_contains_end_of_message( std::string & message_buffer );
		void read_from_socket( int fd, std::string & message_buffer );
		void execute_commands( int fd, std::string & message_buffer );
		void send_queued_messages();
		void remove_unsent_messages_for_disconnected_client( int fd );

		class StopServerException : public std::exception {};
		class NothingMoreToReadException : public std::exception {};
		class DisconnectClientException : public std::exception {};

	public:
		Application( int port, std::string password );
		Application( const Application & src );
		Application & operator=( const Application & rhs );
		virtual ~Application();

		void client_timeout_check( void ); // Separate class
		void launch_server( void );
		void send_message(int socket, const std::string& message);
		void disconnect_client( int fd );

};

#endif /* APPLICATION_H */
