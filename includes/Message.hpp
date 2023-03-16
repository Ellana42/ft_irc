#ifndef MESSAGE_H
#define MESSAGE_H

#include "ft_irc.hpp"
#include "Parsing.hpp"

#define MAX_SIZE 512
#define MIN_SIZE 2

class Message
{
	private:

		std::string command;
		std::map<std::string, std::string> args;

		Parsing *parser;

	public:
		Message( std::string content );
		virtual ~Message();

		std::string get( std::string arg_name );
		/* std::list<std::string> get_list( std::string arg_name ); */
		void parse( void );
		std::string get_command( void );
};
#endif /* MESSAGE_H */
