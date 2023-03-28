#include "Channel.hpp"

Channel::Channel( std::string name )
{
	set_name( name );
}

Channel::Channel( std::string name, User & creator )
{
	set_name( name );
	add_user( creator );
}

Channel::~Channel() {}

void Channel::set_name( std::string name )
{
	/* TODO: Channel name validity check */
	/* throw exception if name is not valid */
	this->name = name;
}

std::string const & Channel::get_name( void ) const
{
	return ( this->name );
}

void Channel::add_user( User & user )
{
	/* std::cout << "CHAN [" << name << "] : Adding user \"" << user.get_nickname() << */
	/*           "\"" << std::endl; */
	users.insert( pair_string_user( user.get_nickname(), &user ) );
}

void Channel::remove_user( User & user )
{
	/* std::cout << "CHAN [" << name << "] : removing user \"" << user.get_nickname() */
	/*           << "\"" << std::endl; */
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

bool Channel::is_empty( void )
{
	std::map<std::string, User *>::iterator it = users.begin();
	if ( it == users.end() )
	{
		return ( true );
	}
	return ( false );
}

std::string Channel::get_user_list( void )
{
	std::string user_list;
	std::map<std::string, User *>::iterator it = users.begin();
	for ( ; it != users.end(); it++ )
	{
		if ( it != users.begin() )
		{
			user_list += " ";
		}
		user_list += it->first;
	}
	return ( user_list );
}
