#include "Context.hpp"
#include "Channel.hpp"
#include <iterator>
#include <sstream>
#include <stdexcept>
#include "Password.hpp"
#include "ft_irc.hpp"
#include "log_event.hpp"

Context::Context( Application & application,
                  Password & password ) : application( application ),
	password_handler( password ),
	message_handler( NULL )
{
	log_event::info( "Context: Creating context" );
	message_handler = new Message_Handler( *this );
	create_channel( DEFAULT_CHAN );
}

Context::~Context()
{
	log_event::info( "Context: Terminating context" );
	delete ( message_handler );
	delete_map( unregistered_users );
	delete_map( registered_users );
	delete_map( channels );
}

void Context::create_unregistered_user( int socket )
{
	User * new_user = new User( *this, socket );
	unregistered_users.insert( pair_int_user ( socket, new_user ) );
}

void Context::register_user( User & user )
{
	if ( user.has_password() == false || user.has_nickname() == false
	        || user.has_user_info() == false )
	{
		return ;
	}
	registered_users.insert( pair_string_user( user.get_nickname(), &user ) );
	unregistered_users.erase( user.get_socket() );
	user.set_registered();
	add_user_to_channel( user, DEFAULT_CHAN );
}

void Context::remove_user( User & user )
{
	if ( user.is_fully_registered() )
	{
		this->remove_registered_user( user );
	}
	else
	{
		this->remove_unregistered_user( user );
	}
}

void Context::remove_user( int socket )
{
	User user = get_user_by_socket( socket );
	remove_user( user );
}

void Context::remove_registered_user( User & user )
{
	log_event::info( "Context: Removing registered user" );
	std::map<std::string, User *>::iterator it = registered_users.find(
	            user.get_nickname() );
	if ( it != registered_users.end() )
	{
		remove_user_from_all_channels( *( it->second ) );
		delete( it->second );
		registered_users.erase( it->first );
	}
}

void Context::remove_unregistered_user( User & user )
{
	log_event::info( "Context: Removing unregistered user" );
	std::map<int, User *>::iterator it = unregistered_users.find(
	        user.get_socket() );
	if ( it != unregistered_users.end() )
	{
		delete( it->second );
		unregistered_users.erase( it->first );
	}
}

void Context::create_channel( std::string name )
{
	Channel * new_chan = new Channel( name, password_handler );
	std::string chan_name = string_to_lowercase( new_chan->get_name() );
	channels.insert( pair_string_chan( chan_name, new_chan ) );
}

void Context::create_channel( User & user, std::string name )
{
	Channel * new_chan = new Channel( name, user, password_handler );
	std::string chan_name = string_to_lowercase( new_chan->get_name() );
	channels.insert( pair_string_chan( chan_name, new_chan ) );
	new_chan->add_operator( user );
}

void Context::add_user_to_channel( User & user, std::string channel_name )
{
	if ( does_channel_exist( channel_name ) == false )
	{
		create_channel( user, channel_name );
	}
	else
	{
		std::string chan_name = string_to_lowercase( channel_name );
		log_event::info( "Context: Adding user \"" + user.get_nickname() +
		                 "\" to channel " + chan_name );
		channels[chan_name]->add_user( user );
		if ( channel_name != DEFAULT_CHAN
		        && channels[DEFAULT_CHAN]->is_user_in_channel( user ) )
		{
			channels[DEFAULT_CHAN]->remove_user( user );
		}
	}
}

void Context::remove_user_from_channel( User & user, std::string channel_name )
{
	if ( does_channel_exist( channel_name ) == false )
	{
		throw std::out_of_range( "Context: Remove from channel: no such channel" );
	}
	else
	{
		std::string chan_name = string_to_lowercase( channel_name );
		log_event::info( "Context: Removing user \"" + user.get_nickname() +
		                 "\" from channel " + chan_name );
		channels[chan_name]->remove_user( user );
		channels[chan_name]->remove_operator( user );
		if ( is_user_in_any_channel( user ) == false && chan_name != DEFAULT_CHAN )
		{
			log_event::info( "Context: Adding user \"" + user.get_nickname() +
			                 "\" to channel *, because user is no longer in any channel" );
			channels[DEFAULT_CHAN]->add_user( user );
		}
	}
}

void Context::remove_user_from_all_channels( User & user )
{
	std::list<Channel *> chans = get_user_channels( user );
	std::list<Channel *>::iterator it = chans.begin();
	for ( ; it != chans.end(); it++ )
	{
		remove_user_from_channel( user, ( *it )->get_name() );
	}
}

bool Context::is_user_in_any_channel( User & user )
{
	std::map<std::string, Channel *>::iterator it = channels.begin();
	for ( ; it != channels.end(); it++ )
	{
		if ( it->second->is_user_in_channel( user ) == true )
		{
			return ( true );
		}
	}
	return ( false );
}

void Context::remove_channel( Channel & channel )
{
	std::string chan_name = string_to_lowercase( channel.get_name() );
	std::map<std::string, Channel *>::iterator it = channels.find( chan_name );
	if ( it != channels.end() )
	{
		delete ( it->second );
		channels.erase( it->first );
	}
}

void Context::handle_message( User & sender, std::string raw_message )
{
	message_handler->handle_message( sender, raw_message );
}

User & Context::get_user_by_socket( int socket )
{
	std::map<int, User *>::iterator u_it = unregistered_users.find( socket );
	if ( u_it != unregistered_users.end() )
	{
		return ( *unregistered_users[socket] );
	}
	std::map<std::string, User *>::iterator r_it = registered_users.begin();
	for ( ; r_it != registered_users.end(); r_it++ )
	{
		if ( r_it->second->get_socket() == socket )
		{
			return ( *r_it->second );
		}
	}
	std::stringstream ss;
	ss << socket;
	throw CouldNotFindUserException();
}

User & Context::get_user_by_nick( std::string nickname )
{
	std::map<std::string, User *>::iterator it = registered_users.find( nickname );
	if ( it != registered_users.end() )
	{
		return ( *registered_users[nickname] );
	}
	throw CouldNotFindUserException();
}

void Context::update_user_nick( User & user, std::string new_nick )
{
	std::map<std::string, User *>::iterator it = registered_users.find(
	            user.get_nickname() );
	if ( it != registered_users.end() )
	{
		std::list<Channel *> chans = get_user_channels( user );
		std::list<Channel *>::iterator it = chans.begin();
		for ( ; it != chans.end(); it++ )
		{
			( *it )->update_user_nick( user, new_nick );
		}
		registered_users.insert( pair_string_user( new_nick, &user ) );
		registered_users.erase( user.get_nickname() );
	}
}

bool Context::does_user_with_nick_exist( std::string nickname )
{
	try
	{
		get_user_by_nick( nickname );
		return ( true );
	}
	catch ( std::exception & e )
	{
		return ( false );
	}
}

Channel & Context::get_channel_by_name( std::string name )
{
	if ( name == DEFAULT_CHAN )
	{
		throw std::out_of_range( "Context: Could not find channel " + name +
		                         " by name" );
	}
	std::string chan_name = string_to_lowercase( name );
	std::map<std::string, Channel *>::iterator it = channels.find( chan_name );
	if ( it != channels.end() )
	{
		return ( *channels[chan_name] );
	}
	throw std::out_of_range( "Context: Could not find channel " + name +
	                         " by name" );
}

Channel & Context::get_default_channel( void )
{
	return ( *channels[DEFAULT_CHAN] );
}

std::list<std::string> Context::get_channel_names( void )
{
	std::list<std::string> channel_names;
	std::map<std::string, Channel *>::iterator it = channels.begin();
	for ( ; it != channels.end(); it++ )
	{
		if ( it->first != DEFAULT_CHAN )
		{
			channel_names.push_back( it->second->get_name() );
		}
	}
	return ( channel_names );
}

bool Context::does_channel_exist( std::string name )
{
	std::string chan_name = string_to_lowercase( name );
	std::map<std::string, Channel *>::iterator it = channels.find( chan_name );
	if ( it != channels.end() )
	{
		return ( true );
	}
	return ( false );
}

std::list<Channel *> Context::get_user_channels( User & user )
{
	std::list<Channel *> user_chans;
	std::map<std::string, Channel *>::iterator it = channels.begin();
	for ( ; it != channels.end(); it++ )
	{
		if ( it->second->is_user_in_channel( user ) == true )
		{
			user_chans.push_back( it->second );
		}
	}
	return ( user_chans );
}

std::list<User *> Context::get_users_in_same_channels( User & user )
{
	std::list<User *> users_in_same_channels;
	std::list<Channel *> chans = get_user_channels( user );
	std::list<Channel *>::iterator it = chans.begin();
	for ( ; it != chans.end(); it++ )
	{
		std::list<User *> chan_users = ( *it )->get_user_list();
		std::list<User *>::iterator uit = chan_users.begin();
		for ( ; uit != chan_users.end(); uit++ )
		{
			if ( *uit != &user && is_in_list( users_in_same_channels, *uit ) == false )
			{
				users_in_same_channels.push_back( *uit );
			}
		}
	}
	return ( users_in_same_channels );
}

void Context::debug_print_unregistered_users( void ) const
{
	std::map<int, User *>::const_iterator it = unregistered_users.begin();
	std::map<int, User *>::const_iterator it_end = unregistered_users.end();
	std::cout << "[INFO] Context: Unregistered users :" << std::endl;
	for ( ; it != it_end; it++ )
	{
		std::cout << "\t[" << it->second->get_socket() << "] "
		          << it->second->get_identifier() << std::endl;
	}
}

void Context::debug_print_registered_users( void ) const
{
	std::map<std::string, User *>::const_iterator it = registered_users.begin();
	std::map<std::string, User *>::const_iterator it_end = registered_users.end();
	std::cout << "[INFO] Context: Registered users :" << std::endl;
	for ( ; it != it_end; it++ )
	{
		std::cout << "\t[" << it->second->get_socket() << "] "
		          << it->second->get_identifier() << std::endl;
	}
}

void Context::debug_print_channels( void ) const
{
	std::map<std::string, Channel *>::const_iterator it = channels.begin();
	std::map<std::string, Channel *>::const_iterator it_end = channels.end();
	std::cout << "[INFO] Context: Channels :" << std::endl;
	for ( ; it != it_end; it++ )
	{
		std::cout << "\t[" << it->second->get_name() << "] ";
	}
	std::cout << std::endl;
}

void Context::check_connection_password( std::string password )
{
	password_handler.validate_connection_password( password );
}

void Context::send_message( int socket, std::string message )
{
	application.send_message( socket, message );
}

void Context::force_disconnect_user( User & user )
{
	application.disconnect_client( user.get_socket() );
}

const char* Context::CouldNotFindUserException::what() const throw()
{
	return ( "Could not find user by name or socket" );
}
