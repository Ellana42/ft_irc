#include "User.hpp"
#include "Context.hpp"

/* User::User() {} */

User::User( Context & context, int socket ) : nickname( "*" ), username( "*" ),
	hostname( "*" ), realname( "*" ), fully_registered( false ), context( context ),
	socket( socket )
{
	update_identifier();
}

User::~User() {}

std::string const & User::get_nickname( void ) const
{
	return ( this->nickname );
}

std::string const & User::get_username( void ) const
{
	return ( this->username );
}

std::string const & User::get_realname( void ) const
{
	return ( this->realname );
}

std::string const & User::get_hostname( void ) const
{
	return ( this->hostname );
}

std::string const & User::get_identifier( void ) const
{
	return ( this->identifier );
}

int const & User::get_socket( void ) const
{
	return ( this->socket );
}

void User::set_nickname( std::string nickname )
{
	this->nickname = nickname;
	this->update_identifier();
}

void User::set_username( std::string username )
{
	this->username = username;
	this->update_identifier();
}

void User::set_realname( std::string realname )
{
	this->realname = realname;
}

void User::set_hostname( std::string hostname )
{
	this->hostname = hostname;
	this->update_identifier();
}

void User::set_registered( void )
{
	if ( this->fully_registered == true )
	{
		throw std::runtime_error( "Attempting to reset already set user registered flag !" );
	}
	this->fully_registered = true;
}

void User::update_identifier( void )
{
	this->identifier = this->nickname + "!" + this->username + "@" + this->hostname;
}

bool User::is_fully_registered( void ) const
{
	return ( this->fully_registered );
}

void User::read_from_socket( void )
{
	std::string raw_message;
	/* TODO: read from socket and store received string in raw_message */
	/* Context will create and handle the message */
	context.handle_message( *this, raw_message );
}

void User::send_reply( std::string reply )
{
	/* send( socket, reply.c_str(), reply.length(), 0 ); */
	std::cout << "[" << socket << "] " << reply << std::endl;
}

bool User::has_nickname( void )
{
	if ( this->nickname != "*" )
	{
		return ( true );
	}
	return ( false );
}

bool User::has_user_info( void )
{
	if ( this->username != "*" && this->hostname != "*"
	        && this->realname != "*" )
	{
		return ( true );
	}
	return ( false );
}
