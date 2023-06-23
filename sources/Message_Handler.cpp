#include "Message_Handler.hpp"
#include "Mode_Handler.hpp"
#include "Mode_Parsing.hpp"
#include "Context.hpp"
#include "Channel.hpp"
#include "Parsing.hpp"
#include "Password.hpp"
#include "log_event.hpp"
#include "reply.hpp"
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
		log_event::warn( "Message Handler: Message creation error: ", e.what() );
		log_event::warn( "--> Message was", raw_message );
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
	if ( sender.is_fully_registered() == true )
	{
		return ( true );
	}
	else if ( sender.has_password() == true
	          && ( command == "USER" || command == "NICK" || command == "CAP"
	               || command == "PASS" || command == "QUIT" ) )
	{
		return ( true );
	}
	else if ( sender.has_password() == false
	          && ( command == "CAP" || command == "PASS" || command == "QUIT" ) )
	{
		return ( true );
	}
	return ( false );
}

void Message_Handler::initialize_message_handlers( void )
{
	handle.insert( pair_handler( "ADMIN", &Message_Handler::handle_admin ) );
	handle.insert( pair_handler( "CAP", &Message_Handler::handle_cap ) );
	handle.insert( pair_handler( "INFO", &Message_Handler::handle_info ) );
	handle.insert( pair_handler( "JOIN", &Message_Handler::handle_join ) );
	handle.insert( pair_handler( "KICK", &Message_Handler::handle_kick ) );
	handle.insert( pair_handler( "LIST", &Message_Handler::handle_list ) );
	handle.insert( pair_handler( "MODE", &Message_Handler::handle_mode ) );
	handle.insert( pair_handler( "NAMES", &Message_Handler::handle_names ) );
	handle.insert( pair_handler( "NICK", &Message_Handler::handle_nick ) );
	handle.insert( pair_handler( "PART", &Message_Handler::handle_part ) );
	handle.insert( pair_handler( "PASS", &Message_Handler::handle_pass ) );
	handle.insert( pair_handler( "PRIVMSG", &Message_Handler::handle_privmsg ) );
	handle.insert( pair_handler( "QUIT", &Message_Handler::handle_quit ) );
	handle.insert( pair_handler( "SUMMON", &Message_Handler::handle_summon ) );
	handle.insert( pair_handler( "USER", &Message_Handler::handle_user ) );
	handle.insert( pair_handler( "USERS", &Message_Handler::handle_users ) );
	handle.insert( pair_handler( "VERSION", &Message_Handler::handle_version ) );
	handle.insert( pair_handler( "INVITE", &Message_Handler::handle_invite ) );
	handle.insert( pair_handler( "TOPIC", &Message_Handler::handle_topic ) );
	handle.insert( pair_handler( "PING", &Message_Handler::handle_ping ) );
	handle.insert( pair_handler( "PONG", &Message_Handler::handle_pong ) );
}

void Message_Handler::handle_admin( Message & message )
{
	User & sender = message.get_sender();
	if ( message.has( "target" ) && message.get( "target" ) != SERVER_NAME )
	{
		sender.send_reply( rpl::err_nosuchserver( sender, message.get( "target" ) ) );
		return ;
	}
	sender.send_reply( rpl::adminme( sender ) );
	sender.send_reply( rpl::adminloc1( sender ) );
	sender.send_reply( rpl::adminloc2( sender ) );
	sender.send_reply( rpl::adminemail( sender ) );
}

void Message_Handler::handle_invite( Message & message )
{
	// TODO: no problem if no such channel
	User & sender = message.get_sender();
	std::string channel_name = message.get( "channel" );
	std::string user_nickname = message.get( "nickname" );

	if ( !context.does_user_with_nick_exist( user_nickname ) )
	{
		sender.send_reply( rpl::err_nosuchnick( sender, user_nickname ) );
		return;
	}
	User & user = context.get_user_by_nick( user_nickname );
	if ( ! context.does_channel_exist( channel_name ) )
	{
		sender.send_reply( rpl::inviting( user, message ) );
		user.send_reply( rpl::invite( sender, message ) );
		return;
	}
	Channel & channel = context.get_channel_by_name( channel_name );
	if ( !channel.is_user_in_channel( sender ) )
	{
		sender.send_reply( rpl::err_notonchannel( sender, channel.get_name() ) );
		return;
	}
	if ( channel.is_invite_only() && !channel.is_operator( sender ) )
	{
		sender.send_reply( rpl::err_chanoprivsneeded( sender, channel_name ) );
		return;
	}
	if ( channel.is_user_in_channel( user_nickname ) )
	{
		sender.send_reply( rpl::err_useronchannel( sender, user_nickname,
		                   channel.get_name() ) );
		return;
	}
	sender.send_reply( rpl::inviting( user, message ) );
	user.send_reply( rpl::invite( sender, message ) );
	channel.add_invited_user( user_nickname );
}

void Message_Handler::handle_topic( Message & message )
{
	User & sender = message.get_sender();
	std::string channel_name = message.get( "channel" );

	if ( !context.does_channel_exist( channel_name ) )
	{
		sender.send_reply( rpl::err_notonchannel( sender, channel_name ) );
		return;
	}
	Channel & channel = context.get_channel_by_name( channel_name );
	if ( !channel.is_user_in_channel( sender ) )
	{
		sender.send_reply( rpl::err_notonchannel( sender, channel.get_name() ) );
		return;
	}
	if ( !message.has( "topic" ) )
	{
		if ( channel.get_topic() == "" )
		{
			sender.send_reply( rpl::notopic( message, channel ) );
			return;
		}
		else
		{
			sender.send_reply( rpl::topic( message, channel ) );
			return;
		}
	}
	std::string new_topic = message.get( "topic" );
	if ( channel.is_topic_restricted() && !channel.is_operator( sender ) )
	{
		sender.send_reply( rpl::err_chanoprivsneeded( sender, channel.get_name() ) );
		return;
	}
	channel.set_topic( new_topic );
	channel.send_reply( rpl::newtopic( sender, message ) );
}

void Message_Handler::handle_cap( Message & message )
{
	( void )message;
	return ;
}

void Message_Handler::handle_info( Message & message )
{
	User & sender = message.get_sender();
	if ( message.has( "target" ) && message.get( "target" ) != SERVER_NAME )
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
	User & sender = message.get_sender();
	std::list<std::string> chan_names = message.get_list( "channel" );
	if ( chan_names.empty() )
	{
		throw std::runtime_error( "Message Handler: JOIN: did not provide channels to join!" );
	}
	if ( chan_names.front() == "0" )
	{
		std::list<Channel *> chan_list = context.get_user_channels( sender );
		std::list<Channel *>::iterator it = chan_list.begin();
		for ( ; it != chan_list.end(); it++ )
		{
			if ( ( *it )->get_name() != DEFAULT_CHAN )
			{
				context.handle_message( sender, rpl::create_part_message( *( *it ) ) );
			}
		}
		return ;
	}
	std::list<std::string> keys;
	for ( size_t i = 0; i < chan_names.size(); i++ )
	{
		keys.push_back( "" );
	}
	if ( message.has_list( "key" ) )
	{
		keys = message.get_list( "key" );
	}
	std::list<std::string>::iterator chans = chan_names.begin();
	std::list<std::string>::iterator passes = keys.begin();
	for ( ; chans != chan_names.end(); chans++, passes++ )
	{
		try
		{
			if ( !context.does_channel_exist( *chans ) )
			{
				context.add_user_to_channel( sender, *chans );
				Channel & channel = context.get_channel_by_name( *chans );
				channel.send_reply( rpl::join_channel( sender, channel ) );
				sender.send_reply( rpl::namreply( sender, channel ) );
				sender.send_reply( rpl::endofnames( sender, channel.get_name() ) );
			}
			else
			{
				Channel & channel = context.get_channel_by_name( *chans );
				if ( channel.is_invite_only() && !channel.is_invited( sender ) )
				{
					sender.send_reply( rpl::err_inviteonlychan( sender, channel.get_name() ) );
				}
				else if ( channel.is_password_protected()
				          &&  !channel.check_password( *passes ) )
				{
					sender.send_reply( rpl::err_badchannelkey( sender, channel.get_name() ) );
				}
				else if ( channel.is_at_limit() )
				{
					sender.send_reply( rpl::err_channelisfull( sender, channel.get_name() ) );
				}
				else
				{
					context.add_user_to_channel( sender, *chans );
					channel.remove_invited_user( sender.get_nickname() );
					channel.send_reply( rpl::join_channel( sender, channel ) );
					sender.send_reply( rpl::topic( message, channel ) );
					sender.send_reply( rpl::namreply( sender, channel ) );
					sender.send_reply( rpl::endofnames( sender, channel.get_name() ) );
				}
			}
		}
		catch ( Channel::AlreadyInChannelException & e )
		{
			log_event::warn( "Message Handler: JOIN: User " + sender.get_nickname() +
			                 " is already in channel " + *chans );
		}
		catch ( std::exception & e )
		{
			log_event::warn( "Message Handler: JOIN: ", e.what() );
			sender.send_reply( rpl::err_nosuchchannel( sender, *chans ) );
		}
	}
}

void Message_Handler::handle_kick( Message & message )
{
	User & sender = message.get_sender();
	std::list<std::string> channels = message.get_list( "channel" );
	std::list<std::string> users = message.get_list( "user" );
	if ( channels.size() > 1 && channels.size() != users.size() )
	{
		// TODO: maybe message.get_command() not correct here
		sender.send_reply( rpl::err_needmoreparams( sender, message.get_command() ) );
		return;
	}

	if ( channels.size() == 1 )
	{
		std::string channel_name = channels.front();
		if ( ! context.does_channel_exist( channel_name ) )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, channel_name ) );
			return;
		}
		Channel & channel = context.get_channel_by_name( channel_name );
		if ( !channel.is_user_in_channel( sender ) )
		{
			sender.send_reply( rpl::err_notonchannel( sender, channel.get_name() ) );
			return;
		}
		if ( !channel.is_operator( sender ) )
		{
			sender.send_reply( rpl::err_chanoprivsneeded( sender, channel_name ) );
			return;
		}
		std::list<std::string>::iterator it = users.begin();
		for ( ; it != users.end(); it++ )
		{
			if ( !context.does_user_with_nick_exist( *it ) )
			{
				sender.send_reply( rpl::err_usernotinchannel( sender, *it,
				                   channel.get_name() ) );
				return;
			}
			User & user = context.get_user_by_nick( *it );
			if ( !channel.is_user_in_channel( user ) )
			{

				sender.send_reply( rpl::err_usernotinchannel( sender, *it,
				                   channel.get_name() ) );
				return;
			}
			if ( message.get( "comment" ) == "" )
			{
				channel.send_reply( rpl::kick( sender, user, channel, sender.get_nickname() ) );
			}
			else
			{
				channel.send_reply( rpl::kick( sender, user, channel,
				                               message.get( "comment" ) ) );
			}
			context.remove_user_from_channel( user, channel.get_name() );
		}
	}
	else
	{
		std::list<std::string>::iterator uit = users.begin();
		std::list<std::string>::iterator cit = channels.begin();
		for ( ; uit != users.end(); uit++, cit++ )
		{
			std::string channel_name = *cit;
			std::string user_name = *uit;
			if ( ! context.does_channel_exist( channel_name ) )
			{
				sender.send_reply( rpl::err_nosuchchannel( sender, channel_name ) );
				return;
			}
			Channel & channel = context.get_channel_by_name( channel_name );
			if ( !channel.is_user_in_channel( sender ) )
			{
				sender.send_reply( rpl::err_notonchannel( sender, channel.get_name() ) );
				return;
			}
			if ( !channel.is_operator( sender ) )
			{
				sender.send_reply( rpl::err_chanoprivsneeded( sender, channel_name ) );
				return;
			}
			if ( !context.does_user_with_nick_exist( user_name ) )
			{
				sender.send_reply( rpl::err_usernotinchannel( sender, user_name,
				                   channel.get_name() ) );
				return;
			}
			User & user = context.get_user_by_nick( user_name );
			if ( !channel.is_user_in_channel( user ) )
			{

				sender.send_reply( rpl::err_usernotinchannel( sender, user_name,
				                   channel.get_name() ) );
				return;
			}
			if ( message.get( "comment" ) == "" )
			{
				channel.send_reply( rpl::kick( sender, user, channel, sender.get_nickname() ) );
			}
			else
			{
				channel.send_reply( rpl::kick( sender, user, channel,
				                               message.get( "comment" ) ) );
			}
			context.remove_user_from_channel( user, channel.get_name() );
		}

	}
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

void Message_Handler::handle_mode( Message & message )
{

	User & sender = message.get_sender();

	Mode_Handler handler( context, sender, message );
	return;
}

void Message_Handler::handle_names( Message & message )
{
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
		catch( std::exception & e )
		{
			log_event::warn( "Message Handler: NAMES:", e.what() );
		}
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
		else
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

void Message_Handler::handle_part( Message & message )
{
	User & sender = message.get_sender();
	std::list<std::string> chan_names = message.get_list( "channel" );
	std::string part_msg = sender.get_nickname();
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
			if ( channel.is_empty() && channel.get_name() != DEFAULT_CHAN )
			{
				context.remove_channel( channel );
			}
		}
		catch( std::exception & e )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, *it ) );
		}
	}
}

void Message_Handler::handle_pass( Message & message )
{
	User & sender = message.get_sender();

	if ( sender.is_fully_registered() )
	{
		sender.send_reply( rpl::err_alreadyregistred( sender ) );
		return ;
	}
	if ( !message.has( "password" ) )
	{
		sender.send_reply( rpl::err_passwdmismatch( sender ) );
		return;
	}
	try
	{
		context.check_connection_password( message.get( "password" ) );
		sender.set_correct_password();
	}
	catch ( Password::InvalidPasswordException & e )
	{
		log_event::warn( "Message_Handler: PASS: ", e.what() );
		sender.send_reply( rpl::err_passwdmismatch( sender ) );
	}
	catch ( std::exception & e )
	{
		log_event::info( "Message_Handler: PASS: ", e.what() );
	}
}

void Message_Handler::handle_privmsg( Message & message )
{
	User & sender = message.get_sender();
	std::string dest_nick = message.get( "msgtarget" );
	std::string text = "";
	if ( message.has( "text to be sent" ) )
	{
		text = message.get( "text to be sent" );
	}
	else
	{
		sender.send_reply( rpl::err_notexttosend( sender ) );
		return;
	}
	if ( context.does_user_with_nick_exist( dest_nick ) == true )
	{
		User & dest_user = context.get_user_by_nick( dest_nick );
		dest_user.send_reply( rpl::forward( sender, message ) );
	}
	else if ( context.does_channel_exist( dest_nick ) == true )
	{
		Channel & dest_chan = context.get_channel_by_name( dest_nick );
		if ( dest_chan.is_user_in_channel( sender ) )
		{
			dest_chan.send_reply( rpl::forward( sender, message ), sender );
		}
		else
		{
			sender.send_reply( rpl::err_cannotsendtochan( sender, dest_chan.get_name() ) );
		}
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
	context.force_disconnect_user( sender );
}

void Message_Handler::handle_summon( Message & message )
{
	User & sender = message.get_sender();
	sender.send_reply( rpl::err_summondisabled( sender ) );
}

void Message_Handler::handle_user( Message & message )
{

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
	catch ( std::exception & e )
	{
		log_event::warn( "Message_Handler: USER:", e.what() );
	}
}

void Message_Handler::handle_users( Message & message )
{
	User & sender = message.get_sender();
	sender.send_reply( rpl::err_usersdisabled( sender ) );
}

void Message_Handler::handle_version( Message & message )
{
	User & sender = message.get_sender();
	sender.send_reply( rpl::server_version( sender ) );
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
	catch ( std::exception & e )
	{
		log_event::warn( "Message Handler: Welcome: ", e.what() );
	}
}

void Message_Handler::handle_ping( Message & message )
{
	User & sender = message.get_sender();

	if ( message.get( "token" ) == "" )
	{
		sender.send_reply( rpl::err_needmoreparams( sender, "PING" ) );
		return;
	}
	sender.send_reply( rpl::pong( sender, message ) );
}

void Message_Handler::handle_pong( Message & message )
{
	( void ) message;
}
