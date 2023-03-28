#ifndef USER_H
#define USER_H

#include "ft_irc.hpp"

#define MAX_USER_SIZE 18

class Context;

class User
{
	private:
		std::string nickname;
		std::string username;
		std::string hostname;
		std::string realname;
		std::string identifier;

		bool fully_registered;
		Context & context;
		int	socket;

		/* User(); */
		void update_identifier( void );

	public:
		User( Context & context, int socket );
		virtual ~User();

		std::string const & get_nickname( void ) const;
		std::string const & get_username( void ) const;
		std::string const & get_realname( void ) const;
		std::string const & get_hostname( void ) const;
		std::string const & get_identifier( void ) const;
		int const & get_socket( void ) const;
		bool is_fully_registered( void ) const;

		void set_nickname( std::string nickname );
		void set_username( std::string username );
		void set_realname( std::string realname );
		void set_hostname( std::string hostname );
		void set_registered( void );

		void read_from_socket( void );
		void send_reply( std::string reply );
		bool has_nickname( void );
		bool has_user_info( void );
};

#endif /* USER_H */
