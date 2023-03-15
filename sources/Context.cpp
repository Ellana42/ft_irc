#include "Context.hpp"

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

Context::Context()
{
	initialize_message_handlers();
}

Context::~Context()
{
	delete_map( unregistered_users );
	delete_map( registered_users );
	/* delete_map( channels ); */
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

bool Context::is_user_nickname_in_use( std::string nickname )
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

void Context::create_unregistered_user( int socket )
{
	User * new_user = new User( *this, socket );
	if ( new_user == NULL )
	{
		throw std::runtime_error( "User creation: Could not allocate memory." );
	}
	unregistered_users.insert( pair_int_user ( socket, new_user ) );
}

void Context::register_user( User & user )
{
	user.set_registered();
	registered_users.insert( pair_string_user( user.get_nickname(), &user ) );
	unregistered_users.erase( user.get_socket() );
}

void Context::handle_message( User & sender, std::string raw_message )
{
	Message message = Message( sender, raw_message );
	if ( should_handle_message( sender, message ) )
	{
		handler function = handle[message.get_command()];
		( *this.*function )( message );
	}
	else
	{
		sender.send_reply( rpl::err_notregistered( sender ) );
	}
}

bool Context::should_handle_message( User & sender, Message message )
{
	if ( sender.is_fully_registered() == false && ( message.get_command() != "USER"
	        || message.get_command() != "NICK" || message.get_command() != "QUIT" ) )
	{
		return ( false );
	}
	return ( true );

}
void Context::initialize_message_handlers( void )
{
	handle.insert( pair_handler( "ADMIN", &Context::handle_admin ) );
	handle.insert( pair_handler( "INFO", &Context::handle_info ) );
	handle.insert( pair_handler( "JOIN", &Context::handle_join ) );
	handle.insert( pair_handler( "KICK", &Context::handle_kick ) );
	handle.insert( pair_handler( "LIST", &Context::handle_list ) );
	handle.insert( pair_handler( "MODE", &Context::handle_mode ) );
	handle.insert( pair_handler( "NAMES", &Context::handle_names ) );
	handle.insert( pair_handler( "NICK", &Context::handle_nick ) );
	handle.insert( pair_handler( "OPER", &Context::handle_oper ) );
	handle.insert( pair_handler( "PART", &Context::handle_part ) );
	handle.insert( pair_handler( "PRIVMSG", &Context::handle_privmsg ) );
	handle.insert( pair_handler( "QUIT", &Context::handle_quit ) );
	handle.insert( pair_handler( "SUMMON", &Context::handle_summon ) );
	handle.insert( pair_handler( "USER", &Context::handle_user ) );
	handle.insert( pair_handler( "USERS", &Context::handle_users ) );
	handle.insert( pair_handler( "VERSION", &Context::handle_version ) );
	handle.insert( pair_handler( "WHO", &Context::handle_who ) );
}

void Context::handle_admin( Message message )
{
	User & sender = message.get_sender();
	std::string target = message.get( "target" );
	if ( !target.empty() )
	{
		sender.send_reply( rpl::err_nosuchserver( sender, target ) );
		return ;
	}
	sender.send_reply( rpl::adminme( sender ) );
	sender.send_reply( rpl::adminloc1( sender ) );
	sender.send_reply( rpl::adminloc2( sender ) );
	sender.send_reply( rpl::adminemail( sender ) );
}

void Context::handle_info( Message message )
{
	User & sender = message.get_sender();
	std::string target = message.get( "target" );
	if ( !target.empty() )
	{
		sender.send_reply( rpl::err_nosuchserver( sender, target ) );
		return ;
	}
	sender.send_reply( rpl::info( sender, 0 ) );
	sender.send_reply( rpl::info( sender, 1 ) );
	sender.send_reply( rpl::info( sender, 2 ) );
	sender.send_reply( rpl::info_end( sender ) );
}

void Context::handle_join( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_kick( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_list( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_mode( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_names( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_nick( Message message )
{
	User & sender = message.get_sender();
	std::string nickname = message.get( "nickname" );
	if ( is_user_nickname_in_use( nickname ) == true )
	{
		sender.send_reply( rpl::err_nicknameinuse( sender, nickname ) );
		return ;
	}
	try
	{
		bool user_had_nickname = sender.has_nickname();
		sender.set_nickname( nickname );
		if ( !user_had_nickname && sender.has_user_info() && sender.has_nickname() )
		{
			register_user( sender );
		}
	}
	catch ( std::exception & e )
	{
		sender.send_reply( rpl::err_erroneusnickname( sender, nickname ) );
	}
}

void Context::handle_oper( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_part( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_privmsg( Message message )
{
	/* TODO: check if sending to channel or user */
	User & from_user = message.get_sender();
	User & to_user = registered_users[message.get( "msgtarget" )];
	to_user.send_reply( rpl::forward( from_user,
	                                  message.get( "text_to_be_sent" ) ) );
}

void Context::handle_quit( Message message )
{
	/* TODO: implement function */
	( void )message;
}

void Context::handle_summon( Message message )
{
	User & sender = message.get_sender();
	sender.send_reply( rpl::err_summondisabled( sender ) );
}

void Context::handle_user( Message message )
{
	/* TODO: add user mode support */
	User & sender = message.get_sender();
	if ( sender.is_fully_registered() )
	{
		sender.send_reply( rpl::err_alreadyregistred( sender ) );
		return ;
	}
	else if ( sender.has_user_info() )
	{
		sender.send_reply( rpl::err_notregistered( sender ) );
		return;
	}
	try
	{
		sender.set_username( message.get( "username" ) );
		/* sender.set_mode( message.get( "mode" ) ); */
		sender.set_hostname( message.get( "hostname" ) );
		sender.set_realname( message.get( "realname" ) );
		if ( sender.has_nickname() && sender.has_user_info() )
		{
			register_user( sender );
		}
	}
	catch ( std::exception & e )
	{
		sender.send_reply( rpl::err_needmoreparams( sender, message.get_command() ) );
	}
}

void Context::handle_users( Message message )
{
	/* TODO: decide if we are implementing function */
	User & sender = message.get_sender();
	sender.send_reply( rpl::err_usersdisabled( sender ) );
}

void Context::handle_version( Message message )
{
	User & sender = message.get_sender();
	sender.send_reply( rpl::server_version( sender ) );
}

void Context::handle_who( Message message )
{
	/* TODO: implement function */
	( void )message;
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

