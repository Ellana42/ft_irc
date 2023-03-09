#ifndef MESSAGE_H
#define MESSAGE_H

#include "ft_irc.hpp"

class Message;

typedef void ( Message::*parse_method )( char * );

class Message
{
	private:

		std::string command;

		std::string content;

		std::string nickname;
		std::string message;
		std::string msgtarget;

		std::string user;
		std::string mode;
		std::string unused;
		std::string realname;

		std::list<std::string> channels;
		std::list<std::string> clients;
		std::list<std::string> names;

		std::map<std::string, parse_method> accepted_commands;

	public:
		Message( std::string content );
		virtual ~Message();

		void parse( void );
		void set_command( std::string command );
		void set_nickname( std::string value );
		void parse_nick( char * str );
		void parse_user( char * str );
		void set_user( std::string value );
		void set_mode( std::string value );
		void set_unused( std::string value );
		void set_realname( std::string value );
		void parse_privmsg( char * str );
		void set_message( std::string value );
		void set_msgtarget( std::string value );
		std::string get_nickname( void );
		std::string get_message( void );
		std::string get_msgtarget( void );
		std::string get_realname( void );
		std::string get_mode( void );
		std::string get_unused( void );
		std::string get_content( void );
		std::string get_user( void );
};
#endif /* MESSAGE_H */
