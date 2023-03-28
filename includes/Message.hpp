#ifndef MESSAGE_H
#define MESSAGE_H

#include "ft_irc.hpp"
#include "Parsing.hpp"
#include "User.hpp"

#define MAX_SIZE 512
#define MIN_SIZE 2

class Message
{
	private:

		std::string command;
		std::map<std::string, std::string> args;
		std::map<std::string, std::list<std::string> > args_list;

		User & sender;

		Parsing * parser;

	public:
		Message( User & sender, std::string content );
		virtual ~Message();

		std::string get( std::string arg_name );
		/* std::list<std::string> get_list( std::string arg_name ); */
		void parse( void );
		std::string get_command( void );
		std::list<std::string> get_list( std::string arg_name );
		bool has( std::string arg_name );
		Parsing get_parser( void );
		User & get_sender( void ) const;
};
#endif /* MESSAGE_H */
