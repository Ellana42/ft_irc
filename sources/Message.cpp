#include "../includes/Message.hpp"
#include <stdexcept>
#include "Parsing.hpp"

Message::Message( User & sender, std::string raw_message ) : sender( sender ),
	parser( NULL )
{
	if ( raw_message.size() > MAX_SIZE )
	{
		throw std::invalid_argument( "Message: Message too long" );
	}
	if ( raw_message.size() < MIN_SIZE )
	{
		throw std::invalid_argument( "Message: Message too short" );
	}
	if ( !( raw_message[raw_message.size() - 2] == '\r'
	        && raw_message[raw_message.size() - 1] == '\n' ) )
	{
		throw std::invalid_argument( "Message: Invalid message end" );
	}
	raw_message.resize( raw_message.size() - 2 );

	parser = new Parsing( raw_message );
}

void Message::parse( void )
{
	parser->parse();
}

Message::~Message( void )
{
	delete parser;
};

std::string Message::get_command( void )
{
	return ( parser->get_command() );
}

Parsing Message::get_parser( void )
{
	return ( *parser );
}

std::string Message::get( std::string arg_name )
{
	if ( parser->has_arg( arg_name ) )
	{
		return ( parser->get( arg_name ) );
	}
	else
	{
		throw std::out_of_range( "Message: argument [" + arg_name +
		                         "] does not exist" );
	}
}

std::list<std::string> Message::get_list( std::string arg_name )
{
	if ( parser->has_list( arg_name ) )
	{
		return ( parser->get_list( arg_name ) );
	}
	else
	{
		throw std::out_of_range( "Message: argument [" + arg_name +
		                         "] does not exist" );
	}
}

bool Message::has( std::string arg_name )
{
	return ( parser->has_arg( arg_name ) );
}

bool Message::has_list( std::string arg_name )
{
	return ( parser->has_list( arg_name ) );
}

User & Message::get_sender( void ) const
{
	return ( sender );
}
