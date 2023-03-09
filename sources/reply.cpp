#include "reply.hpp"
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

std::string const rpl::fwd_privmsg( User sender, Message message )
{
	std::string reply = sender.get_identifier();
	/* reply += " " + message.get_content(); */
	reply += "\r\n";
	( void )message;
	return ( reply );
}
