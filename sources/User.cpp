#include "User.hpp"
#include "Context.hpp"
#include "log_event.hpp"
#include <cstddef>
#include <stdexcept>

/* User::User() {} */

User::User( Context & context, int socket ) : nickname( "*" ), username( "*" ),
	hostname( "*" ), realname( "*" ), fully_registered( false ),
	entered_correct_password( false ), context( context ),
	socket( socket )
{
	update_identifier();
}

User::~User()
{
	log_event::info( "User: closing socket for user \"" + this->nickname + "\": socket", this->socket );
	close( this->socket );
}

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

bool User::is_operator( void ) const
{
	return ( has_mode( 'o' ) );
}

int const & User::get_socket( void ) const
{
	return ( this->socket );
}

std::string const & User::get_mode( void ) const
{
	return ( this->mode );
}

bool User::has_password( void ) const
{
	return ( this->entered_correct_password );
}

void User::set_nickname( std::string nickname )
{
	if ( nickname_is_valid( nickname ) )
	{
		if ( this->is_fully_registered() == true )
		{
			context.update_user_nick( *this, nickname );
		}
		this->nickname = nickname;
		this->update_identifier();
	}
	else
	{
		throw InvalidNicknameException();
	}
}

void User::set_username( std::string username )
{
	if ( username_is_valid( username ) )
	{
		this->username = username.substr( 0, MAX_USER_SIZE );
		this->update_identifier();
	}
	else
	{
		throw InvalidUsernameException();
	}
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
		throw std::runtime_error( "User: Attempting to reset already set user registered flag !" );
	}
	this->fully_registered = true;
}

void User::set_correct_password( void )
{
	if ( this->entered_correct_password == true )
	{
		throw std::runtime_error( "User: Correct password already supplied." );
	}
	this->entered_correct_password = true;
}

void User::set_modes( std::string modes_to_add, std::string modes_to_remove )
{
	add_modes( modes_to_add );
	remove_modes( modes_to_remove );
}


void User::add_modes( std::string mode_string )
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

void User::remove_modes( std::string mode_string )
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

bool User::has_mode( char c ) const
{
	size_t pos = this->mode.find( c, 0 );
	if ( pos != std::string::npos )
	{
		return ( true );
	}
	return ( false );
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
	//send( socket, reply.c_str(), reply.length(), 0 );
	context.send_message( socket, reply );
	log_event::reply( socket, reply );
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

bool User::username_is_valid( std::string username )
{
	const std::string accepted_chars = "@._";

	if ( std::isdigit( username[0] ) )
	{
		return ( false );
	}
	for ( size_t i = 0; i < username.size(); i++ )
	{
		if ( !std::isalnum( username[i] ) && !is_in( username[i], accepted_chars ) )
		{
			return ( false );
		}
	}
	return ( true );
}

bool User::nickname_is_valid( std::string nickname )
{
	const std::string accepted_chars = "_\\^|[]{}`";

	if ( nickname.size() == 0 || nickname.size() > 9 )
	{
		throw NicknameTooLongException();
	}
	if ( std::isdigit( nickname[0] ) )
	{
		return ( false );
	}
	for ( size_t i = 0; i < nickname.size(); i++ )
	{
		if ( !std::isalnum( nickname[i] ) && !is_in( nickname[i], accepted_chars ) )
		{
			return ( false );
		}
	}
	return ( true );
}

std::ostream & operator<<( std::ostream & os, User const & obj )
{
	os << "[" << obj.get_socket() << "][" << obj.get_identifier() << "]";
	return ( os );
}
