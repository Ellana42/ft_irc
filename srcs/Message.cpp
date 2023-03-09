#include "../includes/Message.hpp"

Message::Message( std::string raw_message )
{
	content = raw_message;
	parse();
}

void Message::parse( void )
{

}

void Message::set_command( std::string value )
{
	command = value;
}

void Message::set_nickname( std::string value )
{
	nickname = value;
}

void Message::parse_nick( unsigned int i )
{

}

void Message::parse_user( unsigned int i )
{

}

void Message::set_user( std::string value )
{
	user = value;
}

void Message::set_mode( std::string value )
{
	mode = value;
}

void Message::set_unused( std::string value )
{
	unused = value;
}

void Message::set_realname( std::string value )
{
	realname = value;
}

void Message::parse_privmsg( unsigned int i )
{

}

void Message::set_message( std::string value )
{
	message = value;
}

void Message::set_msgtarget( std::string value )
{
	msgtarget = value;
}

std::string Message::get_nickname( void )
{
	return ( nickname );
}

std::string Message::get_message( void )
{
	return ( message );
}

std::string Message::get_msgtarget( void )
{
	return ( msgtarget );
}

std::string Message::get_realname( void )
{
	return ( realname );
}

std::string Message::get_mode( void )
{
	return ( mode );
}

std::string Message::get_unused( void )
{
	return ( unused );
}

std::string Message::get_content( void )
{
	return ( content );
}

std::string Message::get_user( void )
{
	return ( user );
}
