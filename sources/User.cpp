#include "User.hpp"
#include "Context.hpp"

/* User::User() {} */

User::User( Context & context, int socket ) : nickname( "*" ), username( "*" ),
	hostname( "*" ), context( context ), socket( socket )
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

void User::set_hostname( std::string hostname )
{
	this->hostname = hostname;
	this->update_identifier();
}

void User::update_identifier( void )
{
	this->identifier = this->nickname + "!" + this->username + "@" + this->hostname;
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
	send( socket, reply.c_str(), reply.length(), 0 );
}
