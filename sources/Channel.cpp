#include "Channel.hpp"
#include "Context.hpp"
#include "User.hpp"
#include "log_event.hpp"
#include <cctype>
#include <stdexcept>

Channel::Channel( std::string name ) : topic_restricted( false ),
	invite_only( false ), has_password( false ), has_user_limit( false )
{
	if ( name == DEFAULT_CHAN )
	{
		this->name = DEFAULT_CHAN;
		return ;
	}
	set_name( name );
	log_event::info( "Channel: Created channel", this->name );
}

Channel::Channel( std::string name,
                  User & creator ) : topic_restricted( false ), invite_only( false ),
	has_password( false ), has_user_limit( false )
{
	set_name( name );
	set_creator( creator.get_nickname() );
	add_user( creator );
	log_event::info( "Channel: User " + this->creator_nick + " created channel",
	                 this->name );
}

Channel::~Channel() {}

bool is_chan_name_valid( std::string name )
{
	if ( name.length() > MAX_CHAN_NAME_LENGTH )
	{
		return ( false );
	}
	std::string required_first_char = "&#+!";
	std::string forbidden_chars = " ,:";
	size_t fist_char_check = name.find_first_of( required_first_char, 0 );
	size_t forbbidden_check = name.find_first_of( forbidden_chars, 0 );
	size_t ctrl_g_check = name.find( 7, 0 );
	if ( fist_char_check == 0 && forbbidden_check == std::string::npos
	        && ctrl_g_check == std::string::npos )
	{
		return ( true );
	}
	return ( false );
}

void Channel::set_name( std::string name )
{
	if ( is_chan_name_valid( name ) == true )
	{
		this->name = name;
		return ;
	}
	throw InvalidChannelNameException();
}

std::string const & Channel::get_name( void ) const
{
	return ( this->name );
}

void Channel::set_creator( std::string nick )
{
	this->creator_nick = nick;
	return ;
}

std::string const & Channel::get_creator( void ) const
{
	return ( this->creator_nick );
}

std::string const & Channel::get_mode( void ) const
{
	return ( this->mode );
}

void Channel::add_user( User & user )
{
	log_event::info( "Channel " + this->name + ": Adding user \"" + user.get_nickname() + "\"" );
	if ( is_user_in_channel( user ) == true )
	{
		throw Channel::AlreadyInChannelException();
	}
	users.insert( pair_nick_user( user.get_nickname(), &user ) );
	if ( user.get_nickname() == this->creator_nick )
	{
		add_operator( user );
	}
}

void Channel::remove_user( User & user )
{
	log_event::info( "Channel " + this->name + ": Removing user \"" + user.get_nickname() + "\"" );
	users.erase( user.get_nickname() );
	operators.erase( user.get_nickname() );
}

void Channel::update_user_nick( User & user, std::string new_nick )
{
	std::map<std::string, User *>::iterator it = users.find( user.get_nickname() );
	bool is_chan_creator = is_creator( user );
	if ( it != users.end() )
	{
		users.insert( pair_nick_user( new_nick, &user ) );
		users.erase( user.get_nickname() );
		if ( is_chan_creator == true )
		{
			set_creator( new_nick );
		}
	}
	int is_op = operators.erase( user.get_nickname() );
	if ( is_op )
	{
		operators.insert( new_nick );
	}
}

void Channel::set_modes( std::string modes_to_add, std::string modes_to_remove )
{
	add_modes( modes_to_add );
	remove_modes( modes_to_remove );
}

void Channel::add_modes( std::string mode_string )
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


bool Channel::has_mode( char c )
{
	size_t pos = this->mode.find( c, 0 );
	if ( pos != std::string::npos )
	{
		return ( true );
	}
	return ( false );
}

void Channel::add_operator( User & user )
{
	operators.insert( user.get_nickname() );
}

void Channel::remove_operator( User & user )
{
	operators.erase( user.get_nickname() );
}

void Channel::remove_operator( std::string nick )
{
	operators.erase( nick );
}


bool Channel::is_operator( User & user )
{
	return ( operators.count( user.get_nickname() ) || is_creator( user ) );
}

bool Channel::is_creator( User & user )
{
	if ( user.get_nickname() == this->creator_nick )
	{
		return ( true );
	}
	return ( false );
}

void Channel::add_operator( std::string nickname )
{
	operators.insert( nickname );
}

bool Channel::is_operator( std::string nickname )
{
	return ( operators.count( nickname ) || is_creator( nickname ) );
}

bool Channel::is_creator( std::string nickname )
{
	if ( nickname == this->creator_nick )
	{
		return ( true );
	}
	return ( false );
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

std::list<User *> Channel::get_user_list( void )
{
	std::list<User *> user_list;
	std::map<std::string, User *>::iterator it = users.begin();
	for ( ; it != users.end(); it++ )
	{
		user_list.push_back( it->second );
	}
	return ( user_list );
}

unsigned int Channel::get_nbr_users( void )
{
	return ( users.size() );
}


std::string Channel::get_user_list_string( void )
{
	std::string user_list;
	std::map<std::string, User *>::iterator it = users.begin();
	for ( ; it != users.end(); it++ )
	{
		if ( it != users.begin() )
		{
			user_list += " ";
		}
		if ( is_operator( it->first ) )
		{
			user_list += "@";
		}
		user_list += it->first;
	}
	return ( user_list );
}

const char* Channel::AlreadyInChannelException::what() const throw()
{
	return ( "Channel: user already in channel " );
}

const char* Channel::InvalidChannelNameException::what() const throw()
{
	return ( "Channel: invalid channel name" );
}
