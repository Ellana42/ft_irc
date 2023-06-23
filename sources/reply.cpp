#include "reply.hpp"
#include "Message.hpp"
#include "ft_irc.hpp"
#include "reply_macros.hpp"
#include "reply_macros_error.hpp"
#include "Channel.hpp"
#include <cstdlib>
#include <sstream>

std::string const rpl::liststart( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += "321 ";
	reply += user.get_nickname();
	reply += " Channel : Users Name";
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::list( User & user, Channel & channel )
{
	std::ostringstream nbr_user_str;

	nbr_user_str << channel.get_nbr_users();

	std::string reply = SERVER_PREFIX " ";
	reply += "322 ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel.get_name();
	reply += " ";
	reply += nbr_user_str.str();
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::listend( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += "323 ";
	reply += user.get_nickname();
	reply += " :End of LIST";
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::welcome( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_WELCOME " ";
	reply += user.get_nickname();
	reply += " :Welcome to the Internet Relay Network ";
	reply += user.get_identifier();
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::yourhost( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_YOURHOST " ";
	reply += user.get_nickname();
	reply += " :Your host is ";
	reply += SERVER_NAME;
	reply += ", running version ";
	reply += SERVER_VERSION;
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::created( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_CREATED " ";
	reply += user.get_nickname();
	reply += " :This server was created ";
	reply += SERVER_CREATION;
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::myinfo( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_MYINFO " ";
	reply += user.get_nickname();
	reply += " :";
	reply += SERVER_NAME " ";
	reply += SERVER_VERSION " ";
	reply += "io i";
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::server_version( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_VERSION " ";
	reply += user.get_nickname();
	reply += " " SERVER_VERSION " " SERVER_NAME;
	reply += " :N/A\r\n";
	return ( reply );
}

/* When replying to an ADMIN message, a server */
/* is expected to use replies RPL_ADMINME */
/* through to RPL_ADMINEMAIL and provide a text */
/* message with each.  For RPL_ADMINLOC1 a */
/* description of what city, state and country */
/* the server is in is expected, followed by */
/* details of the institution (RPL_ADMINLOC2) */
/* and finally the administrative contact for the */
/* server (an email address here is REQUIRED) */
/* in RPL_ADMINEMAIL. */
std::string const rpl::adminme( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_ADMINME " ";
	reply += user.get_nickname();
	reply += " " SERVER_NAME;
	reply += " :Administrative info\r\n";
	return ( reply );
}

std::string const rpl::adminloc1( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_ADMINLOC1 " ";
	reply += user.get_nickname();
	reply += " :";
	reply += ADMIN_INFO_1 "\r\n";
	return ( reply );
}

std::string const rpl::adminloc2( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_ADMINLOC2 " ";
	reply += user.get_nickname();
	reply += " :";
	reply += ADMIN_INFO_2 "\r\n";
	return ( reply );
}

std::string const rpl::adminemail( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_ADMINEMAIL " ";
	reply += user.get_nickname();
	reply += " :";
	reply += ADMIN_EMAIL "\r\n";
	return ( reply );
}

/* A server responding to an INFO message is required to */
/* send all its 'info' in a series of RPL_INFO messages */
/* with a RPL_ENDOFINFO reply to indicate the end of the */
/* replies. */
std::string const rpl::info( User & user, int line )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_INFO " ";
	reply += user.get_nickname();
	reply += " :";
	switch ( line )
	{
		case 0:
			reply += "Server name: " SERVER_NAME "\r\n";
			break;
		case 1:
			reply += "Version: " SERVER_VERSION "\r\n";
			break;
		case 2:
			reply += "Created on: " SERVER_CREATION "\r\n";
			break;
	}
	return ( reply );
}

std::string const rpl::info_end( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_ENDOFINFO " ";
	reply += user.get_nickname();
	reply += " :End of INFO list\r\n";
	return ( reply );
}

std::string const rpl::forward( User & sender, Message & message )
{
	std::string reply = ":";
	reply += sender.get_identifier();
	reply += " ";
	reply += message.get_command();
	reply += " ";
	reply += message.get( "msgtarget" );
	reply += " :";
	if ( message.has( "text to be sent" ) )
	{
		reply += message.get( "text to be sent" );
	}
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::confirmation( std::string const identifier,
                                     Message & message )
{
	std::string reply = ":";
	reply += identifier;
	reply += " ";
	reply += message.get_command();
	reply += " ";
	reply += message.get( "nickname" );
	reply += "\r\n";
	return ( reply );
}

/* :coucou!~b@localhost JOIN :#test */
std::string const rpl::join_channel( User & user, Channel & channel )
{
	std::string reply = ":";
	reply += user.get_identifier();
	reply += " JOIN :";
	reply += channel.get_name();
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::mode_channel( User & user, Channel & channel,
                                     std::string mode )
{
	std::string reply = ":";
	reply += user.get_identifier();
	reply += " MODE ";
	reply += channel.get_name();
	reply += " ";
	reply += mode;
	reply += "\r\n";
	return ( reply );
}

/* To reply to a NAMES message, a reply pair consisting */
/* of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the */
/* server back to the client.  If there is no channel */
/* found as in the query, then only RPL_ENDOFNAMES is */
/* returned.  The exception to this is when a NAMES */
/* message is sent with no parameters and all visible */
/* channels and contents are sent back in a series of */
/* RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark */
/* the end. */
/* Message format: "( "=" / "*" / "@" ) <channel> :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )" */
/* "@" is used for secret channels, "*" for private */
/* channels, and "=" for others (public channels). */
std::string const rpl::namreply( User & user, Channel & channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_NAMREPLY " ";
	reply += user.get_nickname();
	reply += " = ";
	reply += channel.get_name();
	reply += " :";
	reply += channel.get_user_list_string();
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::endofnames( User & user, std::string chan_name )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_ENDOFNAMES " ";
	reply += user.get_nickname();
	reply += " ";
	reply += chan_name;
	reply += " :End of NAMES list\r\n";
	return ( reply );
}

std::string const rpl::part( User & user, Channel & channel, Message & message )
{
	std::string reply = ":";
	reply += user.get_identifier();
	reply += " ";
	reply += message.get_command();
	reply += " ";
	reply += channel.get_name();
	reply += " :";
	if ( message.has( "Part Message" ) )
	{
		reply += message.get( "Part Message" );
	}
	else
	{
		reply += user.get_nickname();
	}
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::create_part_message( Channel & channel )
{
	std::string msg = "PART ";
	msg += channel.get_name();
	msg += "\r\n";
	return ( msg );
}

std::string const rpl::quit( User & user, Message & message )
{
	std::string reply = ":";
	reply += user.get_identifier();
	reply += " ";
	reply += message.get_command();
	reply += " :";
	if ( message.has( "Quit Message" ) )
	{
		reply += message.get( "Quit Message" );
	}
	else
	{
		reply += user.get_nickname();
	}
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::inviting( User & user, Message & message )
{
	std::string reply = ":";
	reply += user.get_identifier();
	reply += " ";
	reply += RPL_INVITING " ";
	reply += message.get_sender().get_nickname();
	reply += " ";
	reply += message.get( "nickname" );
	reply += " ";
	reply += message.get( "channel" );
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::invite( User & sender, Message & message )
{
	std::string reply = ":";
	reply += sender.get_identifier();
	reply += " ";
	reply += "INVITE";
	reply += " ";
	reply += message.get( "nickname" );
	reply += " ";
	reply += message.get( "channel" );
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::kick( User & sender, User & user, Channel & channel,
                             std::string comment )
{
	std::string reply = ":";
	reply += sender.get_identifier();
	reply += " ";
	reply += "KICK";
	reply += " ";
	reply += channel.get_name();
	reply += " ";
	reply += user.get_nickname();
	reply += " :";
	reply += comment;
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::notopic( Message & message, Channel & channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_NOTOPIC " ";
	reply += message.get_sender().get_nickname();
	reply += " ";
	reply += channel.get_name();
	reply += " :No topic is set";
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::topic( Message & message, Channel & channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_TOPIC " ";
	reply += message.get_sender().get_nickname();
	reply += " ";
	reply += channel.get_name();
	reply += " :";
	reply += channel.get_topic();
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::umodeis( Message & message, User & user )
{
	( void ) message;
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_UMODEIS " ";
	reply += user.get_nickname();
	reply += " ";
	reply += user.get_mode();
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::channelmodeis( Message & message, Channel & channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_CHANNELMODEIS " ";
	reply += message.get_sender().get_nickname();
	reply += " ";
	reply += channel.get_name();
	reply += " ";
	reply += channel.get_modestring();
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::newtopic( User & sender, Message & message )
{
	std::string reply = ":";
	reply += sender.get_identifier();
	reply += " ";
	reply += "TOPIC";
	reply += " ";
	reply += message.get( "channel" );
	reply += " :";
	reply += message.get( "topic" );
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::pong( User & sender, Message & message )
{
	std::string reply = ":";
	reply += sender.get_identifier();
	reply += " ";
	reply += "PONG";
	reply += " ";
	reply += SERVER_NAME;
	reply += " ";
	reply += message.get( "token" );
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::ping( std::string token )
{
	std::string reply = "";
	reply += "PING";
	reply += " ";
	reply += token;
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::invalidmodeparam( User & sender,
        std::string channel_name, char mode_char, std::string description )
{
	// "<client> <target chan/user> <mode char> <parameter> :<description>"
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_INVALIDMODEPARAM " ";
	reply += sender.get_nickname();
	reply += " ";
	reply += channel_name;
	reply += " ";
	reply += mode_char;
	reply += " :";
	reply += description;
	reply += "\r\n";
	return ( reply );
}
