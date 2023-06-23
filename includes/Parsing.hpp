#ifndef PARSING_H
#define PARSING_H

#include <exception>
#include "ft_irc.hpp"
#include "Tokenizer.hpp"


enum mode {Mandatory, Optional, List, ListOptional, MultiOptional, Special};

class Parsing
{
	private:

		std::string command;

		Tokenizer tokenizer;

		std::vector<std::string> tokens;
		unsigned int	current;

		std::map<std::string, std::string> args;
		std::map<std::string, std::list<std::string> > args_lists;
		void command_to_upper( std::string & command );
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
		void parse_mode( void );
		std::string get_command( void );
		void parse_complex( void );
		bool set_current_arg( std::string arg_name, mode arg_type );
		std::list<std::string> get_rest_tokens( std::string current_token );
		std::list<std::string> arg_to_list( std::string current_token );
		std::string get( std::string arg_name );
		std::list<std::string> get_list( std::string arg_name );

		bool has_arg( std::string arg_name );
		std::vector<std::string> get_tokens( void );
		bool has_list( std::string arg_name );
};

#endif /* PARSING_H */
