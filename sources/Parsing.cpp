#include "../includes/Parsing.hpp"
#include <cstring>
#include <exception>
#include <stdexcept>
#include "Tokenizer.hpp"

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

	if ( !is_in_array( command, accepted_commands, 16 ) )
	{
		throw Parsing::UnknownCommandException();
	}
}

void Parsing::parse( void )
{

}

/* void Parsing::parse_no_arg( void ) */
/* { */
/* 	return ; */
/* } */

/* void Parsing::parse_simple( void ) */
/* { */

/* } */

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

Parsing::~Parsing() {}
