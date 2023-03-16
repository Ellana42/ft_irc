#include "../includes/Message.hpp"
#include <stdexcept>

Message::Message( std::string raw_message )
{
	if ( raw_message.size() > MAX_SIZE )
	{
		throw std::invalid_argument( "Message too long" );
	}
	if ( raw_message.size() < MIN_SIZE )
	{
		throw std::invalid_argument( "Message too short" );
	}
	if ( !( raw_message[raw_message.size() - 1] == '\r'
	        && raw_message[raw_message.size()] == '\n' ) )
	{
		throw std::invalid_argument( "Invalid message end" );
	}
	raw_message.resize( raw_message.size() - 2 );
}

Message::~Message( void ) {};

std::string Message::get( std::string arg_name )
{
	return ( args[arg_name].front() );
}

std::list<std::string> Message::get_list( std::string arg_name )
{
	return ( args[arg_name] );
}

std::string Message::get_command( void )
{
	return ( command );
}

