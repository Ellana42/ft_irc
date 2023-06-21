#ifndef MODE_HANDLER_H
# define MODE_HANDLER_H

#include "Mode_Parsing.hpp"
#include "ft_irc.hpp"
#include "Message.hpp"
#include "reply.hpp"

#include <map>
#include <string>
#include <iostream>


class Context;
class Mode_Handler;

enum TypeTarget {Channel_, User_};

typedef  void ( Mode_Handler::*handler )( void );

class Mode_Handler
{
	private:
		Context & context;
		User & sender;
		Message & message;

		std::map<char, std::map<TypeTarget, std::map<std::string, handler > > >
		handlers;

		std::string target;
		std::list<std::string> arguments;

		std::string added_modes;
		std::string removed_modes;

		TypeTarget type_target;

		ModeParsing * parsing;

		User * target_user;
		Channel * target_channel;

		bool set_type();
		bool set_modestring();
		void set_arguments();
		bool has_unknown_modes( std::string modes );
		bool has_unknown_modes( char mode );
		void apply_modes();

		// Handlers
		void handle_i_user_add();
		void handle_i_user_rm();

		void handle_i_channel_add();
		void handle_i_channel_rm();
		void handle_t_channel_add();
		void handle_t_channel_rm();
		void handle_k_channel_add();
		void handle_k_channel_rm();
		void handle_o_channel_add();
		void handle_o_channel_rm();
		void handle_l_channel_add();
		void handle_l_channel_rm();

		void move( void );
		std::string get_current_argument();
		std::string filter_modes( std::string modestring );

	public:
		Mode_Handler( Context & context, User & sender, Message & message );
		virtual ~Mode_Handler( void );

		void handle_mode( Message & message, User & sender );
};

#endif
