#include "../includes/Message.hpp"

Message::Message( std::string raw_message )
{
	content = raw_message;
	/* accepted_commands["NICK"] = &Message::parse_nick; */
	/* accepted_commands["USER"] = &Message::parse_user; */
	/* accepted_commands["PRIVMSG"] = &Message::parse_privmsg; */
	parse();
}

Message::~Message( void ) {};

void Message::parse( void )
{
	char *parsing = ( char * )content.c_str();

	set_command( std::strtok( parsing, " " ) );
	if ( command == "NICK" )
	{
		parse_nick( parsing );
	}
	else if ( command == "USER" )
	{
		parse_user( parsing );
	}
	else if ( command == "PRIVMSG" )
	{
		parse_privmsg( parsing );
	}
}

void Message::set_command( std::string value )
{
	command = value;
}

void Message::set_nickname( std::string value )
{
	nickname = value;
}

void Message::parse_nick( char *parsing )
{
	set_nickname( std::strtok( parsing, "\r" ) );
}

void Message::parse_user( char *parsing )
{
	set_user( std::strtok( parsing, " " ) );
	set_mode( std::strtok( parsing, " " ) );
	set_unused( std::strtok( parsing, " " ) );
	parsing++;
	set_realname( std::strtok( parsing, "\r" ) );
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

void Message::parse_privmsg( char *parsing )
{
	set_msgtarget( std::strtok( parsing, " " ) );
	parsing++;
	set_message( std::strtok( parsing, "\r" ) );
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
