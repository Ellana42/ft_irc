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
		Context & context;
		int	socket;

		/* User(); */

	public:
		User( Context & context, int socket );
		~User();

		std::string const & get_nickname( void ) const;
		std::string const & get_username( void ) const;
		std::string const & get_hostname( void ) const;
		void set_nickname( std::string nickname );
		void set_username( std::string username );
		void set_hostname( std::string hostname );

		void send_reply( std::string reply );

};

#endif /* USER_H */
