#include "../includes/Parsing.hpp"
#include <cstring>
#include <exception>
#include <stdexcept>
#include "Tokenizer.hpp"

Parsing::Parsing( std::string raw_content ) : tokenizer( Tokenizer(
	            raw_content ) ), current( 0 )
{
	tokenizer.tokenize();
	tokens = tokenizer.get_tokens();
	if ( tokens.size() == 0 )
	{
		throw
	}
	/* commands["ADMIN"].push_back( "target" ); */
	/* modes["ADMIN"].push_back( Optional ); */

	/* commands["INFO"].push_back( "target" ); */
	/* modes["INFO"].push_back( Optional ); */
	/* commands["JOIN"].push_back( "channel" ); */
	/* modes["JOIN"].push_back( List ); */
	/* commands["JOIN"].push_back( "key" ); */
	/* modes["JOIN"].push_back( ListOptional ); */

	/* commands["KICK"].push_back( "channel" ); */
	/* modes["KICK"].push_back( List ); */
	/* commands["KICK"].push_back( "user" ); */
	/* modes["KICK"].push_back( List ); */
	/* commands["KICK"].push_back( "comment" ); */
	/* modes["KICK"].push_back( ListOptional ); */

	/* commands["LIST"].push_back( "channel" ); */
	/* modes["LIST"].push_back( ListOptional ); */
	/* commands["LIST"].push_back( "target" ); */
	/* modes["LIST"].push_back( Optional ); */

	/* commands["MODE"].push_back( "channel" ); */
	/* modes["MODE"].push_back( Mandatory ); */
	/* commands["MODE"].push_back( "modes" ); */
	/* modes["MODE"].push_back( Special ); */
	/* commands["MODE"].push_back( "modeparams" ); */
	/* modes["MODE"].push_back( Special ); */
}

void Parsing::parse( void )
{

}

void Parsing::parse_no_arg( void )
{
	return ;
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

Parsing::~Parsing() {}
