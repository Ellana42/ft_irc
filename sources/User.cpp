#include "User.hpp"

/* User::User() {} */
User::User( Context & context, int socket ) : context( context ),
	socket( socket ) {}
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
void User::set_nickname( std::string nickname )
{
	this->nickname = nickname;
}
void User::set_username( std::string username )
{
	this->username = username;
}
void User::set_hostname( std::string hostname )
{
	this->hostname = hostname;
}

void User::send_reply( std::string reply )
{
	send( socket, reply.c_str(), reply.length(), 0 );
}
