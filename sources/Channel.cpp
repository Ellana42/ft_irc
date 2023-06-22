#include "Channel.hpp"
#include "Context.hpp"
#include "Password.hpp"
#include "User.hpp"
#include "log_event.hpp"
#include <cctype>
#include <stdexcept>

Channel::Channel( std::string name,
                  Password & password_handler ) : topic_restricted( false ),
	invite_only( false ), has_password( false ), has_user_limit( false ),
	password_handler( password_handler )
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
                  User & creator, Password & password_handler ) : topic_restricted( false ),
	invite_only( false ),
	has_password( false ), has_user_limit( false ),
	password_handler( password_handler )
{
	set_name( name );
	set_creator( creator.get_nickname() );
	add_user( creator );
	log_event::info( "Channel: User " + this->creator_nick + " created channel",
	                 this->name );
}

Channel::~Channel() {}

void Channel::set_topic( std::string new_topic )
{
	topic = new_topic;
}

std::string Channel::get_topic( void ) const
{
	return ( topic );
}

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
	log_event::info( "Channel " + this->name + ": Adding user \"" +
	                 user.get_nickname() + "\"" );
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
	log_event::info( "Channel " + this->name + ": Removing user \"" +
	                 user.get_nickname() + "\"" );
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

void Channel::add_invited_user( std::string nick )
{
	invited_users.insert( nick );
}

void Channel::remove_invited_user( std::string nick )
{
	invited_users.erase( nick );
}

void Channel::flush_invites( void )
{
	invited_users.clear();
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

void Channel::send_reply( std::string reply, User & user_to_ignore )
{
	std::map<std::string, User *>::iterator it = users.begin();
	for ( ; it != users.end(); it++ )
	{
		if ( it->first != user_to_ignore.get_nickname() )
		{
			it->second->send_reply( reply );
		}
	}
}

bool Channel::is_user_in_channel( std::string nickname )
{
	std::map<std::string, User *>::iterator it = users.find( nickname );
	if ( it != users.end() )
	{
		return ( true );
	}
	return ( false );
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

void Channel::set_topic_restricted( bool setting )
{
	topic_restricted = setting;
}

bool Channel::is_topic_restricted() const
{
	return topic_restricted;
}

void Channel::set_invite_only( bool setting )
{
	invite_only = setting;
}

bool Channel::is_invite_only() const
{
	return invite_only;
}

void Channel::set_password( std::string password )
{
	channel_password = password_handler.get_hash( password );
	has_password = true;
}

void Channel::remove_password()
{
	channel_password = "";
	has_password = false;
}

bool Channel::is_password_protected() const
{
	return has_password;
}

bool Channel::check_password( std::string password ) const
{
	if ( !has_password )
	{
		return true;
	}
	try
	{
		password_handler.validate_password( channel_password, password );
		return ( true );
	}
	catch ( Password::InvalidPasswordException & e )
	{
		return ( false );
	}
}

void Channel::set_user_limit( int limit )
{
	user_limit = limit;
	has_user_limit = true;
}

void Channel::remove_user_limit(  )
{
	has_user_limit = false;
}

bool Channel::has_user_limitation() const
{
	return has_user_limit;
}

bool Channel::is_at_limit() const
{
	if ( has_user_limit && users.size() >= user_limit )
	{
		return ( true );
	}
	return ( false );
}


bool Channel::is_invited( User & user ) const
{
	return invited_users.count( user.get_nickname() );
}

bool Channel::is_invited( std::string nickname ) const
{
	return invited_users.count( nickname );
}

const char* Channel::AlreadyInChannelException::what() const throw()
{
	return ( "Channel: user already in channel " );
}

const char* Channel::InvalidChannelNameException::what() const throw()
{
	return ( "Channel: invalid channel name" );
}

std::string Channel::get_modestring( void ) const
{
	std::string modestring = "+";

	if ( has_user_limit )
	{
		modestring += "l";
	}
	if ( invite_only )
	{
		modestring += "i";
	}
	if ( has_password )
	{
		modestring += "k";
	}
	if ( topic_restricted )
	{
		modestring += "t";
	}
	return modestring;
}
