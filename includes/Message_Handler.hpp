#ifndef MESSAGE_HANDLER_H
# define MESSAGE_HANDLER_H

# include "ft_irc.hpp"
# include "Message.hpp"
# include "reply.hpp"
# include "Mode_Handler.hpp"

class Context;

class Message_Handler
{
	private:
		typedef void ( Message_Handler::*handler )( Message & message );
		typedef std::pair<std::string, handler> pair_handler;

		Context & context;
		std::map<std::string, handler> handle;

		void initialize_message_handlers( void );

		void handle_admin( Message & message );
		void handle_cap( Message & message );
		void handle_info( Message & message );
		void handle_join( Message & message );
		void handle_kick( Message & message );
		void handle_list( Message & message );
		void handle_mode(  Message & message );
		void handle_names( Message & message );
		void handle_nick( Message & message );
		void handle_oper( Message & message );
		void handle_part( Message & message );
		void handle_pass( Message & message );
		void handle_privmsg( Message & message );
		void handle_quit( Message & message );
		void handle_summon( Message & message );
		void handle_user( Message & message );
		void handle_users( Message & message );
		void handle_version( Message & message );
		void handle_who( Message & message );
		void handle_invite( Message & message );
		void handle_topic( Message & message );
		void handle_ping( Message & message );
		void handle_pong( Message & message );

		bool should_handle_message( User & sender, Message & message );
		Message * create_message( User & sender, std::string raw_message );
		void check_message_validity( User & sender, Message & message );
		void welcome_user( User & user );
		bool username_is_valid( std::string username );

	public:
		Message_Handler( Context & context );
		virtual ~Message_Handler( void );

		void handle_message( User & sender, std::string raw_message );
};

#endif
