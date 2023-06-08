#ifndef MODE_HANDLER_H
# define MODE_HANDLER_H

#include "Mode_Parsing.hpp"
#include "ft_irc.hpp"
#include "Message.hpp"
#include "reply.hpp"
#include <map>


class Context;
class Mode_Handler;

enum TypeTarget {Channel_, User_};

typedef  void ( Mode_Handler::*handler )( void );

class Mode_Handler
{
	private:
		static const std::string accepted_modes;
		Context & context;
		User & sender;
		Message & message;

		std::map<char, std::map<TypeTarget, std::map<std::string, handler > > >
		handlers;

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

		// Handlers
		void handle_i_user_add();
		void handle_i_user_rm();
		void handle_i_channel_add();
		void handle_i_channel_rm();
		void handle_o_user_add();
		void handle_o_user_rm();
		void handle_o_channel_add();
		void handle_o_channel_rm();
		void handle_O_user_add();
		void handle_O_user_rm();
		void handle_O_channel_add();
		void handle_O_channel_rm();

	public:
		Mode_Handler( Context & context, User & sender, Message & message );
		virtual ~Mode_Handler( void );

		void handle_mode( Message & message, User & sender );
};

#endif
