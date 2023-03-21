#include "../includes/Parsing.hpp"
#include <algorithm>
#include <cstring>
#include <exception>
#include <stdexcept>
#include "Tokenizer.hpp"

std::string accepted_commands[17] = {"ADMIN", "INFO", "JOIN", "KICK",
                                     "LIST", "MODE", "NAMES", "NICK",
                                     "OPER", "PART", "PRIVMSG", "QUIT",
                                     "SUMMON", "USER", "USERS", "VERSION", "WHO"
                                    };

std::string no_params[4] = {"ADMIN", "INFO", "VERSION", "USERS"};

std::string params[12] = {"NICK", "OPER", "PRIVMSG", "USER", "QUIT", "JOIN", "LIST", "NAMES", "SUMMON", "WHO", "KICK", "PART"};
std::string params_names[12][10] = {{"nickname"}, {"name", "password"}, {"msgtarget", "text to be sent"}, {"user", "mode", "unused", "realname"}, {"Quit Message"}, {"channel", "key"}, {"channel", "target"}, {"channel", "target"}, {"user", "target", "channel"}, {"mask", "o"}, {"channel", "user", "comment"}, {"channel", "Part Message"}};
mode params_states[12][10] = {{Mandatory}, {Mandatory, Mandatory}, {Mandatory, Mandatory}, {Mandatory, Mandatory, Mandatory, Mandatory}, {Optional}, {List, ListOptional}, {ListOptional, Optional}, {ListOptional, Optional}, {Mandatory, Optional, Optional}, {Optional, Optional}, {List, List, Optional}, {List, Optional}};


template<typename T>
bool is_in_array( T value, T array[], unsigned int size_array )
{
	for ( unsigned int i = 0; i < size_array; i++ )
	{
		if ( value == array[i] )
		{
			return ( true );
		}
	}
	return ( false );
}

template<typename T>
unsigned int get_array_index( T value, T array[], unsigned int size_array )
{
	for ( unsigned int i = 0; i < size_array; i++ )
	{
		if ( value == array[i] )
		{
			return ( i );
		}
	}
	return ( -1 );
}

Parsing::Parsing( std::string raw_content ) : tokenizer( Tokenizer(
	            raw_content ) ), current( 0 )
{
	tokenizer.tokenize();
	tokens = tokenizer.get_tokens();
	if ( tokens.size() == 0 )
	{
		throw Parsing::UnknownCommandException();
	}
	command = tokens[0];
	move();
}

void Parsing::parse( void )
{
	if ( !is_in_array( command, accepted_commands, 16 ) )
	{
		throw Parsing::UnknownCommandException();
	}

	if ( is_in_array( command, no_params, 4 ) )
	{
		parse_no_arg();
	}
	else if ( is_in_array( command, params, 8 ) )
	{
		try
		{
			parse_complex();
		}
		catch ( std::out_of_range const &e )
		{
			throw NeedMoreParamsException();
		}
	}
}

void Parsing::parse_no_arg( void )
{
	if ( tokens.size() > 1 )
	{
		throw Parsing::TooManyParamsException();
	}
	return;
}

void Parsing::parse_complex( void )
{
	unsigned int command_index = get_array_index( command, params, 12 );
	unsigned int i = 0;
	std::string current_param = params_names[command_index][i] ;
	mode current_type = params_states[command_index][i] ;

	while ( !current_param.empty() )
	{
		if ( !set_current_arg( current_param, current_type ) )
		{
			throw NeedMoreParamsException();
		}
		move();
		i++;
		current_param = params_names[command_index][i] ;
	}
	if ( tokens.size() > i + 1 )
	{
		throw TooManyParamsException();
	}
}

std::string Parsing::get_current_token()
{
	if ( current >= tokens.size() )
	{
		throw std::out_of_range( "No more tokens" );
	}
	return ( tokens[current] );
}

bool Parsing::set_current_arg( std::string arg_name )
{
	try
	{
		std::string current_token = get_current_token();
		args[arg_name] = current_token;
		return ( true );
	}
	catch ( std::out_of_range const &e )
	{
		return ( false );
	}
}

std::list<std::string> Parsing::arg_to_list( std::string current_token )
{
	std::list<std::string> args_list;

	char *token = ( char * )current_token.c_str();

	char * subtoken = std::strtok( token, "," );
	args_list.push_back( ( std::string )subtoken );
	while ( subtoken != NULL )
	{
		subtoken = strtok( NULL, "," );
		args_list.push_back( subtoken );
	}
	return args_list;
}

bool Parsing::set_current_arg( std::string arg_name, mode arg_type )
{
	try
	{
		std::string current_token = get_current_token();
		if ( arg_type == List || arg_type == ListOptional )
		{
			args_lists[arg_name] = arg_to_list( current_token );
		}
		else
		{
			args[arg_name] = current_token;
		}
	}
	catch ( std::out_of_range const &e )
	{
		if ( arg_type == Mandatory || arg_type == List )
		{
			return ( false );
		}
		return ( true );
	}
	return ( true );
}

bool Parsing::set_current_arg_list( std::string arg_name )
{
	char *subtoken;

	try
	{
		std::string current_token = get_current_token();
		char *token = ( char * )current_token.c_str();

		subtoken = std::strtok( token, "," );
		args[arg_name] = subtoken;
		while ( subtoken != NULL )
		{
			subtoken = strtok( NULL, "," );
			args[arg_name] = subtoken;
		}
		return ( true );
	}
	catch ( std::out_of_range const &e )
	{
		return ( false );
	}
}

void Parsing::move( void )
{
	current++;
}

std::string Parsing::get_command( void )
{
	return ( command );
}

std::string Parsing::get( std::string arg_name )
{
	return ( args[arg_name] );
}

std::list<std::string> Parsing::get_list( std::string arg_name )
{
	return ( args_lists[arg_name] );
}

bool Parsing::has_arg( std::string arg_name )
{
	// XXX might be improved by checking the command type and which arguments should exist
	if ( args.count( arg_name ) == 0 && args_lists.count( arg_name ) == 0 )
	{
		return ( false );
	}
	return ( true );
}

Parsing::~Parsing() {}

const char* Parsing::NeedMoreParamsException::what() const throw()
{
	return ( "Not enough parameters provided" );
}

const char* Parsing::TooManyParamsException::what() const throw()
{
	return ( "Too many parameters provided" );
}

const char* Parsing::UnknownCommandException::what() const throw()
{
	return ( "Unknown command" );
}
