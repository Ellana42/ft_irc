#include "Message_Handler.hpp"
#include "Context.hpp"
#include "Channel.hpp"
#include <exception>
#include <list>
#include <stdexcept>

Message_Handler::Message_Handler( Context & context ) : context( context )
{
	initialize_message_handlers();
}

Message_Handler::~Message_Handler( void ) {}

void Message_Handler::handle_message( User & sender, std::string raw_message )
{
	Message * message = NULL;

	try
	{
		message = create_message( sender, raw_message );

		check_message_validity( sender, *message );
		if ( should_handle_message( sender, *message ) )
		{
			handler function = handle[message->get_command()];
			( *this.*function )( *message );
		}
		else
		{
			sender.send_reply( rpl::err_notregistered( sender ) );
		}
		delete ( message );
	}
	catch ( std::exception & e )
	{
		std::cerr << "Message creation error: " << e.what()
		          << " (Message was: [" << raw_message << "] )" << std::endl;
		if ( message != NULL )
		{
			delete ( message );
		}
		return ;
	}
}

Message * Message_Handler::create_message( User & sender,
        std::string raw_message )
{
	Message * message = NULL;
	try
	{
		message = new Message( sender, raw_message );
	}
	catch ( Parsing::UnknownCommandException & e )
	{
		sender.send_reply( rpl::err_unknowncommand( sender, "" ) );
		throw std::runtime_error( e.what() );
	}
	catch ( std::exception & e )
	{
		throw std::runtime_error( e.what() );
	}
	return ( message );
}

void Message_Handler::check_message_validity( User & sender, Message & message )
{
	try
	{
		message.parse();
	}
	catch ( Parsing::TooManyParamsException & e )
	{
		sender.send_reply( rpl::err_toomanyparams( sender, message.get_command() ) );
		throw std::runtime_error( e.what() );
	}
	catch ( Parsing::NeedMoreParamsException & e )
	{
		sender.send_reply( rpl::err_needmoreparams( sender, message.get_command() ) );
		throw std::runtime_error( e.what() );
	}
	catch ( Parsing::UnknownCommandException & e )
	{
		sender.send_reply( rpl::err_unknowncommand( sender, message.get_command() ) );
		throw std::runtime_error( e.what() );
	}
	catch ( std::exception & e )
	{
		throw std::runtime_error( e.what() );
	}
}

bool Message_Handler::should_handle_message( User & sender, Message & message )
{
	std::string command = message.get_command();
	if ( sender.is_fully_registered() == true || command == "USER"
	        || command == "NICK" || command == "QUIT" )
	{
		return ( true );
	}
	return ( false );
}
void Message_Handler::initialize_message_handlers( void )
{
	handle.insert( pair_handler( "ADMIN", &Message_Handler::handle_admin ) );
	handle.insert( pair_handler( "INFO", &Message_Handler::handle_info ) );
	handle.insert( pair_handler( "JOIN", &Message_Handler::handle_join ) );
	handle.insert( pair_handler( "KICK", &Message_Handler::handle_kick ) );
	handle.insert( pair_handler( "LIST", &Message_Handler::handle_list ) );
	handle.insert( pair_handler( "MODE", &Message_Handler::handle_mode ) );
	handle.insert( pair_handler( "NAMES", &Message_Handler::handle_names ) );
	handle.insert( pair_handler( "NICK", &Message_Handler::handle_nick ) );
	handle.insert( pair_handler( "OPER", &Message_Handler::handle_oper ) );
	handle.insert( pair_handler( "PART", &Message_Handler::handle_part ) );
	handle.insert( pair_handler( "PRIVMSG", &Message_Handler::handle_privmsg ) );
	handle.insert( pair_handler( "QUIT", &Message_Handler::handle_quit ) );
	handle.insert( pair_handler( "SUMMON", &Message_Handler::handle_summon ) );
	handle.insert( pair_handler( "USER", &Message_Handler::handle_user ) );
	handle.insert( pair_handler( "USERS", &Message_Handler::handle_users ) );
	handle.insert( pair_handler( "VERSION", &Message_Handler::handle_version ) );
	handle.insert( pair_handler( "WHO", &Message_Handler::handle_who ) );
}

void Message_Handler::handle_admin( Message & message )
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

void Message_Handler::handle_info( Message & message )
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

void Message_Handler::handle_join( Message & message )
{
	/* TODO: handle "0" as param to part with all channels */
	User & sender = message.get_sender();
	std::list<std::string> chan_names = message.get_list( "channel" );
	if ( chan_names.empty() )
	{
		throw std::runtime_error( "JOIN: did not provide channels to join!" );
	}
	/* TODO: if first chan name is 0, add condition here and part all user chans */
	/* TODO: add security so you can't JOIN "*" */
	std::list<std::string>::iterator it = chan_names.begin();
	for ( ; it != chan_names.end(); it++ )
	{
		try
		{
			context.add_user_to_channel( sender, *it );
			Channel & channel = context.get_channel_by_name( *it );
			channel.send_reply( rpl::join_channel( sender, channel ) );
			sender.send_reply( rpl::namreply( sender, channel ) );
			sender.send_reply( rpl::endofnames( sender, channel.get_name() ) );
		}
		catch ( std::exception & e )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, *it ) );
		}
	}
}

void Message_Handler::handle_kick( Message & message )
{
	/* TODO: implement function */
	( void )message;
}

void Message_Handler::handle_list( Message & message )
{
	/* TODO: implement function */
	( void )message;
}

void Message_Handler::handle_mode( Message & message )
{
	/* TODO: implement function */
	( void )message;
}

void Message_Handler::handle_names( Message & message )
{
	User & sender = message.get_sender();
	std::list<std::string> chan_names = message.get_list( "channel" );
	bool show_default_chan = false;
	if ( chan_names.empty() )
	{
		chan_names = context.get_channel_names();
		show_default_chan = true;
	}
	std::list<std::string>::iterator it = chan_names.begin();
	std::list<std::string>::iterator last = ( ++chan_names.rbegin() ).base();
	for ( ; it != chan_names.end(); it++ )
	{
		try
		{
			Channel & channel = context.get_channel_by_name( *it );
			sender.send_reply( rpl::namreply( sender, channel ) );
		}
		catch( std::exception & e ) {}
		if ( show_default_chan == false && it == last )
		{
			sender.send_reply( rpl::endofnames( sender, *it ) );
		}
	}
	if ( show_default_chan == true )
	{
		Channel & channel = context.get_default_channel();
		if ( channel.is_empty() == false )
		{
			sender.send_reply( rpl::namreply( sender, channel ) );
		}
		sender.send_reply( rpl::endofnames( sender, channel.get_name() ) );
	}
}

void Message_Handler::handle_nick( Message & message )
{
	User & sender = message.get_sender();
	std::string nickname = message.get( "nickname" );
	if ( context.does_user_with_nick_exist( nickname ) == true )
	{
		sender.send_reply( rpl::err_nicknameinuse( sender, nickname ) );
		return ;
	}
	try
	{
		bool user_is_already_registered = sender.is_fully_registered();
		std::string old_id = sender.get_identifier();
		sender.set_nickname( nickname );
		if ( user_is_already_registered )
		{
			sender.send_reply( rpl::confirmation( old_id, message ) );
		}
		else if ( !user_is_already_registered )
		{
			welcome_user( sender );
		}
	}
	catch ( std::exception & e )
	{
		sender.send_reply( rpl::err_erroneusnickname( sender, nickname ) );
	}
}

void Message_Handler::handle_oper( Message & message )
{
	/* TODO: implement function */
	( void )message;
}

void Message_Handler::handle_part( Message & message )
{
	User & sender = message.get_sender();
	std::list<std::string> chan_names = message.get_list( "channel" );
	std::string part_msg = message.get( "Part Message" );
	std::list<std::string>::iterator it = chan_names.begin();
	for ( ; it != chan_names.end(); it++ )
	{
		try
		{
			Channel & channel = context.get_channel_by_name( *it );
			if ( channel.is_user_in_channel( sender ) == false )
			{
				sender.send_reply( rpl::err_notonchannel( sender, channel.get_name() ) );
				continue ;
			}
			context.remove_user_from_channel( sender, *it );
			channel.send_reply( rpl::part( sender, channel, message ) );
			sender.send_reply( rpl::part( sender, channel, message ) );
		}
		catch( std::exception & e )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, *it ) );
		}
	}

}

void Message_Handler::handle_privmsg( Message & message )
{
	User & sender = message.get_sender();
	std::string dest_nick = message.get( "msgtarget" );
	std::string text = message.get( "text to send" );
	if ( text.empty() )
	{
		sender.send_reply( rpl::err_notexttosend( sender ) );
	}
	if ( context.does_user_with_nick_exist( dest_nick ) == true )
	{
		User & dest_user = context.get_user_by_nick( dest_nick );
		dest_user.send_reply( rpl::forward( sender, message ) );
	}
	else if ( context.does_channel_exist( dest_nick ) == true )
	{
		Channel & dest_chan = context.get_channel_by_name( dest_nick );
		dest_chan.send_reply( rpl::forward( sender, message ) );
	}
	else
	{
		sender.send_reply( rpl::err_nosuchnick( sender, dest_nick ) );
	}
}

void Message_Handler::handle_quit( Message & message )
{
	/* TODO: implement function */
	( void )message;
}

void Message_Handler::handle_summon( Message & message )
{
	User & sender = message.get_sender();
	sender.send_reply( rpl::err_summondisabled( sender ) );
}

void Message_Handler::handle_user( Message & message )
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
	sender.set_username( message.get( "username" ) );
	/* sender.set_mode( message.get( "mode" ) ); */
	sender.set_hostname( message.get( "unused" ) );
	sender.set_realname( message.get( "realname" ) );
	welcome_user( sender );
}

void Message_Handler::handle_users( Message & message )
{
	/* TODO: decide if we are implementing function */
	User & sender = message.get_sender();
	sender.send_reply( rpl::err_usersdisabled( sender ) );
}

void Message_Handler::handle_version( Message & message )
{
	User & sender = message.get_sender();
	sender.send_reply( rpl::server_version( sender ) );
}

void Message_Handler::handle_who( Message & message )
{
	/* TODO: implement function */
	( void )message;
}

void Message_Handler::welcome_user( User & user )
{
	if ( user.has_nickname() == false || user.has_user_info() == false )
	{
		return ;
	}
	try
	{
		context.register_user( user );
		user.send_reply( rpl::welcome( user ) );
		user.send_reply( rpl::yourhost( user ) );
		user.send_reply( rpl::created( user ) );
		user.send_reply( rpl::myinfo( user ) );
	}
	catch ( std::exception & e ) {}
}
