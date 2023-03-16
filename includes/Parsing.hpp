#ifndef PARSING_H
#define PARSING_H

#include <exception>
#include "../includes/ft_irc.hpp"
#include "Tokenizer.hpp"


/* enum mode {Mandatory, Optional, List, ListOptional, Special}; */

class Parsing
{
	private:

		std::string command;
		std::map<std::string, std::list<std::string> > args;

		Tokenizer tokenizer;

		/* std::map<std::string, std::list<std::string> > commands; */
		/* std::map<std::string, std::list<mode> > modes; */
		std::vector<std::string> tokens;
		unsigned int	current;

	public:
		Parsing( std::string raw_content );
		virtual ~Parsing();
		std::string get_current_token();
		bool set_current_arg( std::string arg_name );
		bool set_current_arg_list( std::string arg_name );
		void parse( void );
		void move( void );

		class TooManyParamsException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class NeedMoreParamsException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class UnknownCommandException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		void parse_no_arg( void );
		void parse_simple( void );
		std::string get_command( void );
};

#endif /* PARSING_H */
