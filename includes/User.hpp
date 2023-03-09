#ifndef USER_H
#define USER_H

#include "Context.hpp"
#include "ft_irc.hpp"

class User
{
	private:
		std::string nickname;
		std::string username;
		std::string hostname;
		std::string identifier;
		Context & context;
		int	socket;

		/* User(); */
		void update_identifier( void );

	public:
		User( Context & context, int socket );
		~User();

		std::string const & get_nickname( void ) const;
		std::string const & get_username( void ) const;
		std::string const & get_hostname( void ) const;
		std::string const & get_identifier( void ) const;

		void set_nickname( std::string nickname );
		void set_username( std::string username );
		void set_hostname( std::string hostname );

		void send_reply( std::string reply );
};

#endif /* USER_H */
