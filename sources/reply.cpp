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

std::string const rpl::forward( User sender, Message message )
{
	std::string reply = ":";
	reply += sender.get_identifier();
	/* reply += " " + message.get_content(); */
	reply += "\r\n";
	( void )message;
	return ( reply );
}
