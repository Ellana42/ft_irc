#ifndef CONTEXT_H
#define CONTEXT_H

#include "ft_irc.hpp"
#include "Message.hpp"
#include "reply.hpp"
#include "Message_Handler.hpp"

class User;
/* class Channel; */


class Context
{
	private:
		typedef std::pair<std::string, User *> pair_string_user;
		typedef std::pair<int, User *> pair_int_user;

		std::map<int, User *> unregistered_users;
		std::map<std::string, User *> registered_users;
		/* std::map<std::string, Channel> channels; */

		Message_Handler * message_handler;

		Context( const Context & src );
		Context & operator=( const Context & rhs );

	public:
		Context();
		~Context();

		void create_unregistered_user( int socket );
		void register_user( User & user );
		/* void add_new_channel( Channel & channel); */
		void handle_message( User & sender, std::string raw_message );

		User & get_user_by_socket( int socket );
		User & get_user_by_nick( std::string nickname );
		bool is_user_nickname_in_use( std::string nickname );

		void debug_print_unregistered_users( void ) const;
		void debug_print_registered_users( void ) const;
};

#endif /* CONTEXT_H */
