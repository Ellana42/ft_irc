#ifndef CONTEXT_H
#define CONTEXT_H

#include "ft_irc.hpp"
#include "Message.hpp"
#include "reply.hpp"

class User;
/* class Channel; */


class Context
{
	private:
		typedef void ( Context::*handler )( Message & message );
		typedef std::pair<std::string, handler> pair_handler;
		typedef std::pair<std::string, User *> pair_string_user;
		typedef std::pair<int, User *> pair_int_user;

		std::map<int, User *> unregistered_users;
		std::map<std::string, User *> registered_users;
		/* std::map<std::string, Channel> channels; */

		std::map<std::string, handler> handle;

		void initialize_message_handlers( void );

		void handle_admin( Message & message );
		void handle_info( Message & message );
		void handle_join( Message & message );
		void handle_kick( Message & message );
		void handle_list( Message & message );
		void handle_mode( Message & message );
		void handle_names( Message & message );
		void handle_nick( Message & message );
		void handle_oper( Message & message );
		void handle_part( Message & message );
		void handle_privmsg( Message & message );
		void handle_quit( Message & message );
		void handle_summon( Message & message );
		void handle_user( Message & message );
		void handle_users( Message & message );
		void handle_version( Message & message );
		void handle_who( Message & message );

		bool is_user_nickname_in_use( std::string nickname );
		bool should_handle_message( User & sender, Message & message );
		Message * create_message( User & sender, std::string raw_message );
		void check_message_validity( User & sender, Message & message );

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

		void debug_print_unregistered_users( void ) const;
		void debug_print_registered_users( void ) const;
};

#endif /* CONTEXT_H */
