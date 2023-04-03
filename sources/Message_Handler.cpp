#include "Message_Handler.hpp"
#include "Mode_Parsing.hpp"
#include "Context.hpp"
#include "Channel.hpp"
#include "Parsing.hpp"
#include <cctype>
#include <exception>
#include <list>
#include <stdexcept>
#include <string>

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
	if ( message.has( "target" ) )
	{
		sender.send_reply( rpl::err_nosuchserver( sender, message.get( "target" ) ) );
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
	if ( message.has( "target" ) )
	{
		sender.send_reply( rpl::err_nosuchserver( sender, message.get( "target" ) ) );
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
		catch ( Channel::AlreadyInChannelException & e ) {}
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
	User & sender = message.get_sender();
	std::list<std::string> channels;

	sender.send_reply( rpl::liststart( sender ) );
	if ( message.has_list( "channel" ) )
	{
		channels = message.get_list( "channel" );
		std::list<std::string>::iterator it = channels.begin();
		for ( ; it != channels.end(); it++ )
		{
			sender.send_reply( rpl::list( sender, context.get_channel_by_name( *it ) ) );
		}
	}
	else
	{
		channels = context.get_channel_names();
		std::list<std::string>::iterator it = channels.begin();
		for ( ; it != channels.end(); it++ )
		{
			sender.send_reply( rpl::list( sender, context.get_channel_by_name( *it ) ) );
		}
	}
	sender.send_reply( rpl::listend( sender ) );
}

bool has_unknown_modes( std::string modes, std::string accepted_modes )
{
	for ( unsigned int i = 0; i < modes.size(); i++ )
	{
		if ( !is_in( modes[i], accepted_modes ) )
		{
			return ( true );
		}
	}
	return ( false );
}

void Message_Handler::handle_mode( Message & message )
{
	User & sender = message.get_sender();

	const std::string accepted_modes = "oO";
	std::string target = message.get( "target" );
	TypeTarget type_target = Channel_;
	User * target_user;
	Channel * target_channel;

	if ( is_channel( target ) )
	{
		if ( !context.does_channel_exist( target ) )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, target ) );
			return;
		}
		target_channel = &context.get_channel_by_name( target );
	}
	else
	{
		if ( !context.does_user_with_nick_exist( target ) )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, target ) );
			return;
		}
		type_target = User_;
		target_user = &context.get_user_by_nick( target );
		if ( target != sender.get_nickname() )
		{
			sender.send_reply( rpl::err_usersdontmatch( sender ) );
			return;
		}
	}

	if ( message.has( "modestring" ) )
	{
		ModeParsing parsing( message.get( "modestring" ) );
		try
		{
			// TODO: filter operators that aren't o or O
			parsing.parse();
			std::string added_modes = parsing.get_added_modes();
			std::string removed_modes = parsing.get_removed_modes();
			if ( has_unknown_modes( added_modes, accepted_modes )
			        || has_unknown_modes( removed_modes, accepted_modes ) )
			{
				sender.send_reply( rpl::err_umodeunknownflag( sender ) );
			}

			if ( type_target == User_ )
			{
				target_user->set_modes( added_modes, removed_modes );
			}
			else
			{
				target_channel->set_modes( added_modes, removed_modes );
			}
		}
		catch ( ModeParsing::InvalidModestringException & e )
		{
			sender.send_reply( rpl::err_invalidmodestring() );
		}
	}
	else
	{
		// TODO: implement rpl umodeis
		return;
	}
	if ( message.has( "mode arguments" ) )
	{
		// TODO: implement
	}
}

void Message_Handler::handle_names( Message & message )
{
	// TODO: special print for channel operators
	User & sender = message.get_sender();
	std::list<std::string> chan_names;
	bool show_default_chan = false;
	if ( message.has_list( "channel" ) )
	{
		chan_names = message.get_list( "channel" );
	}
	else
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
	catch ( User::InvalidNicknameException & e )
	{
		sender.send_reply( rpl::err_erroneusnickname( sender, nickname ) );
	}
	catch ( User::NicknameTooLongException & e )
	{
		sender.send_reply( rpl::err_nicknametoolong( sender, nickname ) );
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
	std::string part_msg = "";
	if ( message.has( "Part Message" ) )
	{
		part_msg = message.get( "Part Message" );
	}
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
	std::string text = message.get( "text to be sent" );
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
	User & sender = message.get_sender();
	if ( context.is_user_in_any_channel( sender ) == true )
	{
		std::list<User *> users_in_same_channels = context.get_users_in_same_channels(
		            sender );
		std::list<User *>::iterator it = users_in_same_channels.begin();
		for ( ; it != users_in_same_channels.end(); it++ )
		{

			( *it )->send_reply( rpl::quit( sender, message ) );
		}
	}
	context.remove_user( sender );
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

	try
	{

		sender.set_username( message.get( "user" ) );
		sender.set_hostname( message.get( "unused" ) );
		sender.set_realname( message.get( "realname" ) );
		welcome_user( sender );
		/* sender.set_mode( message.get( "mode" ) ); */
	}
	catch ( User::InvalidUsernameException & e )
	{
		sender.send_reply( rpl::err_invalidusername() );
	}
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
	// TODO: special print for channel operators
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
