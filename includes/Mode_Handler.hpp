#ifndef MODE_HANDLER_H
# define MODE_HANDLER_H

#include "Mode_Parsing.hpp"
#include "ft_irc.hpp"
#include "Message.hpp"
#include "reply.hpp"
#include <map>


class Context;

enum TypeTarget {Channel_, User_};

class Mode_Handler
{
	private:
		static const std::string accepted_modes;
		Context & context;
		User & sender;
		Message & message;

		std::map<std::string, void ( Mode_Handler::* )( void )> handlers;

		std::string target;
		std::string added_modes;
		std::string removed_modes;

		TypeTarget type_target;

		ModeParsing * parsing;

		User * target_user;
		Channel * target_channel;

		void set_type();
		void set_modestring();
		bool has_unknown_modes( std::string modes );
		void apply_modes();
		void handle_i_user();
		void handle_i_channel();
		void handle_o_user();
		void handle_o_channel();

	public:
		Mode_Handler( Context & context, User & sender, Message & message );
		virtual ~Mode_Handler( void );

		void handle_mode( Message & message, User & sender );
};

#endif
