#include "Channel.hpp"

Channel::Channel( std::string name, User & creator ) : name( name )
{
	add_user_to_channel( creator );
}

Channel::~Channel() {}

void Channel::set_name( std::string name )
{
	/* TODO: Channel name validity check */
	this->name = name;
}

std::string const & Channel::get_name( void ) const
{
	return ( this->name );
}

void Channel::add_user_to_channel( User & user )
{
	users.insert( pair_string_user( user.get_nickname(), &user ) );
}

void Channel::remove_user_from_channel( User & user )
{
	users.erase( user.get_nickname() );
}

void Channel::send_reply( std::string reply )
{
	std::map<std::string, User *>::iterator it = users.begin();
	for ( ; it != users.end(); it++ )
	{
		it->second->send_reply( reply );
	}
}

bool Channel::is_user_in_channel( User & user )
{
	std::map<std::string, User *>::iterator it = users.find( user.get_nickname() );
	if ( it != users.end() )
	{
		return ( true );
	}
	return ( false );
}
