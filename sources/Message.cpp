#include "../includes/Message.hpp"
#include <stdexcept>
#include "Parsing.hpp"

Message::Message( User * sender, std::string raw_message ) : sender( sender ),
	parser( NULL )
{
	if ( raw_message.size() > MAX_SIZE )
	{
		throw std::invalid_argument( "Message too long" );
	}
	if ( raw_message.size() < MIN_SIZE )
	{
		throw std::invalid_argument( "Message too short" );
	}
	if ( !( raw_message[raw_message.size() - 2] == '\r'
	        && raw_message[raw_message.size() - 1] == '\n' ) )
	{
		throw std::invalid_argument( "Invalid message end" );
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

std::string Message::get( std::string arg_name )
{
	return ( parser->get( arg_name ) );
}

std::list<std::string> Message::get_list( std::string arg_name )
{
	return ( parser->get_list( arg_name ) );
}

bool Message::has( std::string arg_name )
{
	return ( parser->has_arg( arg_name ) );
}

User * Message::get_sender( void ) const
{
	return ( sender );
}
