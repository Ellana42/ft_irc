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
	users.insert( pair_user_string( &user, "" ) );
}

void Channel::remove_user( User & user )
{
	/* std::cout << "CHAN [" << name << "] : removing user \"" << user.get_nickname() */
	/*           << "\"" << std::endl; */
	users.erase( &user );
}

void Channel::set_modes( std::string mode_string )
{
	std::string::iterator it = mode_string.begin();
	for ( ; it != mode_string.end(); it++ )
	{
		size_t pos = this->mode.find( *it, 0 );
		if ( pos == std::string::npos )
		{
			this->mode += *it;
		}
	}
}

void Channel::remove_modes( std::string mode_string )
{
	std::string::iterator it = mode_string.begin();
	for ( ; it != mode_string.end(); it++ )
	{
		size_t pos = this->mode.find( *it, 0 );
		if ( pos != std::string::npos )
		{
			this->mode.erase( pos, 1 );
		}
	}
}

void Channel::set_modes( User & user, std::string mode_string )
{
	if ( is_user_in_channel( user ) == true )
	{
		user.set_modes( mode_string );
	}
}

void Channel::remove_modes( User & user, std::string mode_string )
{
	if ( is_user_in_channel( user ) == true )
	{
		user.remove_modes( mode_string );
	}
}

void Channel::send_reply( std::string reply )
{
	std::map<User *, std::string>::iterator it = users.begin();
	for ( ; it != users.end(); it++ )
	{
		it->first->send_reply( reply );
	}
}

bool Channel::is_user_in_channel( User & user )
{
	std::map<User *, std::string>::iterator it = users.find( &user );
	if ( it != users.end() )
	{
		return ( true );
	}
	return ( false );
}

bool Channel::is_empty( void )
{
	std::map<User *, std::string>::iterator it = users.begin();
	if ( it == users.end() )
	{
		return ( true );
	}
	return ( false );
}

std::string Channel::get_user_list( void )
{
	std::string user_list;
	std::map<User *, std::string>::iterator it = users.begin();
	for ( ; it != users.end(); it++ )
	{
		if ( it != users.begin() )
		{
			user_list += " ";
		}
		user_list += it->first->get_nickname();
	}
	return ( user_list );
}
