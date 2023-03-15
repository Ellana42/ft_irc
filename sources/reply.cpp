#include "reply.hpp"
#include "ft_irc.hpp"
#include "reply_macros.hpp"
#include "reply_macros_error.hpp"

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

std::string const rpl::yourhost( void )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_YOURHOST;
	reply += " :Your host is ";
	reply += SERVER_NAME;
	reply += ", running version ";
	reply += SERVER_VERSION;
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::created( void )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_CREATED;
	reply += " :This server was created ";
	reply += SERVER_CREATION;
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::myinfo( void )
{
	std::string reply = SERVER_PREFIX " ";
	reply += RPL_MYINFO;
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
# define RPL_ADMINME "256"
# define RPL_ADMINME_MSG "<server> :Administrative info"
# define RPL_ADMINLOC1 "257"
# define RPL_ADMINLOC1_MSG ":<admin info>"
# define RPL_ADMINLOC2 "258"
# define RPL_ADMINLOC3_MSG ":<admin info>"
# define RPL_ADMINEMAIL "259"
# define RPL_ADMINEMAIL_MSG ":<admin info>"

std::string const rpl::forward( User & sender, Message message )
{
	std::string reply = ":";
	reply += sender.get_identifier();
	/* reply += " " + message.get_content(); */
	reply += "\r\n";
	( void )message;
	return ( reply );
}
