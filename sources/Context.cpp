#include "Context.hpp"
#include "Channel.hpp"

template <typename T, typename U>
void delete_map( std::map<T, U> & map )
{
	typename std::map<T, U>::iterator it = map.begin();
	for ( ; it != map.end(); it++ )
	{
		delete ( it->second );
	}
	map.clear();
}

Context::Context() : message_handler( NULL )
{
	message_handler = new Message_Handler( *this );
	create_channel( DEFAULT_CHAN );
}

Context::~Context()
{
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
	if ( user.has_nickname() == false || user.has_user_info() == false )
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

void Context::remove_registered_user( User & user )
{
	std::map<std::string, User *>::iterator it = registered_users.find(
	            user.get_nickname() );
	if ( it != registered_users.end() )
	{
		delete( it->second );
		registered_users.erase( it->first );
	}
}

void Context::remove_unregistered_user( User & user )
{
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
	Channel * new_chan = new Channel( name );
	channels.insert( pair_string_chan( name, new_chan ) );
}

void Context::create_channel( User & user, std::string name )
{
	Channel * new_chan = new Channel( name, user );
	channels.insert( pair_string_chan( name, new_chan ) );
}

void Context::add_user_to_channel( User & user, std::string channel_name )
{
	if ( does_channel_exist( channel_name ) == false )
	{
		create_channel( user, channel_name );
	}
	else
	{
		channels[channel_name]->add_user( user );
	}
	if ( channels[DEFAULT_CHAN]->is_user_in_channel( user ) )
	{
		channels[DEFAULT_CHAN]->remove_user( user );
	}
}

void Context::remove_user_from_channel( User & user, std::string channel_name )
{
	if ( does_channel_exist( channel_name ) == false )
	{
		return ;
	}
	else
	{
		channels[channel_name]->remove_user( user );
		if ( is_user_in_any_channel( user ) == false )
		{
			channels[DEFAULT_CHAN]->add_user( user );
		}
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
	std::map<std::string, Channel *>::iterator it = channels.find(
	            channel.get_name() );
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
	throw std::out_of_range( "Could not find user by socket" );
}

User & Context::get_user_by_nick( std::string nickname )
{
	std::map<std::string, User *>::iterator it = registered_users.find( nickname );
	if ( it != registered_users.end() )
	{
		return ( *registered_users[nickname] );
	}
	throw std::out_of_range( "Could not find user by nickname" );
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
	std::map<std::string, Channel *>::iterator it = channels.find( name );
	if ( it != channels.end() )
	{
		return ( *channels[name] );
	}
	throw std::out_of_range( "Could not find channel by name" );
}

bool Context::does_channel_exist( std::string name )
{
	std::map<std::string, Channel *>::iterator it = channels.find( name );
	if ( it != channels.end() )
	{
		return ( true );
	}
	return ( false );
}

void Context::debug_print_unregistered_users( void ) const
{
	std::map<int, User *>::const_iterator it = unregistered_users.begin();
	std::map<int, User *>::const_iterator it_end = unregistered_users.end();
	std::cout << "Unregistered users :" << std::endl;
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
	std::cout << "Registered users :" << std::endl;
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
	std::cout << "Channels :" << std::endl;
	for ( ; it != it_end; it++ )
	{
		std::cout << "\t[" << it->second->get_name() << "] ";
	}
	std::cout << std::endl;
}
