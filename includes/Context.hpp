#ifndef CONTEXT_H
#define CONTEXT_H

#include "ft_irc.hpp"
#include "Message.hpp"
#include "User.hpp"

class User;
/* class Channel; */

class Context
{
	private:
		std::map<int, User *> unregistered_users;
		std::map<std::string, User *> registered_users;
		/* std::map<std::string, Channel> channels; */

		Context( const Context & src );
		Context & operator=( const Context & rhs );

	public:
		Context();
		~Context();

		void create_unregistered_user( int socket );
		void move_user_to_registered( User & user );
		/* void add_new_channel( Channel & channel); */
		/* void execute_message( User & sender, Message message ); */
		/* void transmit_message( void ); */

		User & get_user_by_socket( int socket );
		User & get_user_by_nick( std::string nickname );

		void debug_print_unregistered_users( void ) const;
		void debug_print_registered_users( void ) const;
};

std::ostream & operator<<( std::ostream & os, Context const & obj );

#endif /* CONTEXT_H */
