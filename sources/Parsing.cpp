#include "../includes/Parsing.hpp"
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

std::string simple_params[4] = {"NICK", "OPER", "PRIVMSG", "USER"};
std::string params[4][4] = {{"nickname"}, {"name", "password"}, {"msgtarget", "text to be sent"}, {"user", "mode", "unused", "realname"}};


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
	return ;
}

void Parsing::parse_no_arg( void )
{
	if ( tokens.size() > 1 )
	{
		throw Parsing::TooManyParamsException();
	}
	return;
}

void Parsing::parse_simple( void )
{

}

std::string Parsing::get_current_token()
{
	if ( current > tokens.size() )
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
		args[arg_name].push_back( current_token );
		return ( true );
	}
	catch ( std::out_of_range )
	{
		return ( false );
	}
}

bool Parsing::set_current_arg_list( std::string arg_name )
{
	char *subtoken;

	try
	{
		std::string current_token = get_current_token();
		char *token = ( char * )current_token.c_str();

		subtoken = std::strtok( token, "," );
		args[arg_name].push_back( subtoken );
		while ( subtoken != NULL )
		{
			subtoken = strtok( NULL, "," );
			args[arg_name].push_back( subtoken );
		}
		return ( true );
	}
	catch ( std::out_of_range )
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
