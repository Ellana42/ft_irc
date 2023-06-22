#include "reply.hpp"
#include "reply_macros.hpp"
#include "reply_macros_error.hpp"

/* Used to indicate the nickname parameter supplied to a */
/* command is currently unused. */
std::string const rpl::err_nosuchnick( User & user,
                                       std::string name_or_channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOSUCHNICK " ";
	reply += user.get_nickname();
	reply += " ";
	reply += name_or_channel;
	reply += " :No such nick/channel\r\n";
	return ( reply );
}

/* Used to indicate the username parameter supplied is */
/* problematic */
std::string const rpl::err_invalidusername( void )
{
	std::string reply = "ERROR :Invalid user name\r\n";
	return ( reply );
}

/* Used to indicate the modestring parameter supplied is */
/* problematic */
std::string const rpl::err_invalidmodestring( void )
{
	std::string reply = "ERROR :Invalid mode string\r\n";
	return ( reply );
}

/* Used to indicate the server name given currently */
/* does not exist. */
std::string const rpl::err_nosuchserver( User & user, std::string server_name )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOSUCHSERVER " ";
	reply += user.get_nickname();
	reply += " ";
	reply += server_name;
	reply += " :No such server\r\n";
	return ( reply );
}

/* Used to indicate the given channel name is invalid. */
std::string const rpl::err_nosuchchannel( User & user,
        std::string channel_name )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOSUCHCHANNEL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel_name;
	reply += " :No such channel\r\n";
	return ( reply );
}

/* Sent to a user who is either (a) not on a channel */
/* which is mode +n or (b) not a chanop (or mode +v) on */
/* a channel which has mode +m set or where the user is */
/* banned and is trying to send a PRIVMSG message to */
/* that channel. */
std::string const rpl::err_cannotsendtochan( User & user,
        std::string channel_name )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_CANNOTSENDTOCHAN " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel_name;
	reply += " :Cannot send to channel\r\n";
	return ( reply );
}

/* Sent to a user when they have joined the maximum */
/* number of allowed channels and they try to join */
/* another channel. */
std::string const rpl::err_toomanychannels( User & user,
        std::string channel_name )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_TOOMANYCHANNELS " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel_name;
	reply += " :You have joined too many channels\r\n";
	return ( reply );
}

/* Returned by WHOWAS to indicate there is no history */
/* information for that nickname. */
std::string const rpl::err_wasnosuchnick( User & user, std::string nickname )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_WASNOSUCHNICK " ";
	reply += user.get_nickname();
	reply += " ";
	reply += nickname;
	reply += " :There was no such nickname\r\n";
	return ( reply );
}

/* - Returned to a client which is attempting to send a */
/*   PRIVMSG/NOTICE using the user@host destination format */
/*   and for a user@host which has several occurrences. */
/* - Returned to a client which trying to send a */
/*   PRIVMSG/NOTICE to too many recipients. */
/* - Returned to a client which is attempting to JOIN a safe */
/*   channel using the shortname when there are more than one */
/*   such channel. */
std::string const rpl::err_toomanytargets( User & user, std::string target,
        int error_code,
        std::string abort_message )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_TOOMANYTARGETS " ";
	reply += user.get_nickname();
	reply += " ";
	reply += target;
	reply += " :";
	reply += error_code;
	reply += " recipients. ";
	reply += abort_message;
	reply += "\r\n";
	return ( reply );
}

/* Returned to a client which is attempting to send a SQUERY */
/* to a service which does not exist. */
std::string const rpl::err_nosuchservice( User & user,
        std::string service_name )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOSUCHSERVICE " ";
	reply += user.get_nickname();
	reply += " ";
	reply += service_name;
	reply += " :No such service\r\n";
	return ( reply );
}

/* - PING or PONG message missing the originator parameter. */
std::string const rpl::err_noorigin( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOORIGIN " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :No origin specified\r\n";
	return ( reply );
}

/* 412 - 415 are returned by PRIVMSG to indicate that */
/* the message wasn't delivered for some reason. */
std::string const rpl::err_norecipient( User & user, std::string command )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NORECIPIENT " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :No recipient given (";
	reply += command;
	reply += ")\r\n";
	return ( reply );
}

/* 412 - 415 are returned by PRIVMSG to indicate that */
/* the message wasn't delivered for some reason. */
std::string const rpl::err_notexttosend( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOTEXTTOSEND " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :No text to send\r\n";
	return ( reply );
}

/* ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that */
/* are returned when an invalid use of */
/* "PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted. */
std::string const rpl::err_notoplevel( User & user, std::string mask )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOTOPLEVEL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += mask;
	reply += " :No toplevel domain specified\r\n";
	return ( reply );
}

/* ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that */
/* are returned when an invalid use of */
/* "PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted. */
std::string const rpl::err_wildtoplevel( User & user, std::string mask )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_WILDTOPLEVEL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += mask;
	reply += " :Wildcard in toplevel domain\r\n";
	return ( reply );
}

/* 412 - 415 are returned by PRIVMSG to indicate that */
/* the message wasn't delivered for some reason. */
std::string const rpl::err_badmask( User & user, std::string mask )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_BADMASK " ";
	reply += user.get_nickname();
	reply += " ";
	reply += mask;
	reply += " :Bad Server/host mask\r\n";
	return ( reply );
}

/* Returned to a registered client to indicate that the */
/* command sent is unknown by the server. */
std::string const rpl::err_unknowncommand( User & user, std::string command )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_UNKNOWNCOMMAND " ";
	reply += user.get_nickname();
	reply += " ";
	reply += command;
	reply += " :Unknown command\r\n";
	return ( reply );
}

/* Server's MOTD file could not be opened by the server. */
std::string const rpl::err_nomotd( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOMOTD " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :MOTD File is missing\r\n";
	return ( reply );
}

/* Returned by a server in response to an ADMIN message */
/* when there is an error in finding the appropriate */
/* information. */
std::string const rpl::err_noadmininfo( User & user, std::string server )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOADMININFO " ";
	reply += user.get_nickname();
	reply += " ";
	reply += server;
	reply += " :No administrative info available\r\n";
	return ( reply );
}

/* Generic error message used to report a failed file */
/* operation during the processing of a message. */
std::string const rpl::err_fileerror( User & user, std::string file_operation,
                                      std::string filename )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_FILEERROR " ";
	reply += user.get_nickname();
	reply += " ";
	reply += ":File error doing ";
	reply += file_operation;
	reply += " on ";
	reply += filename;
	reply += "\r\n";
	return ( reply );
}

/* Returned when a nickname parameter expected for a */
/* command and isn't found. */
std::string const rpl::err_nonicknamegiven( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NONICKNAMEGIVEN " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :No nickname given\r\n";
	return ( reply );
}

/* Returned after receiving a NICK message which contains */
/* characters which do not fall in the defined set.  See */
/* section 2.3.1 for details on valid nicknames. */
std::string const rpl::err_erroneusnickname( User & user, std::string nickname )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_ERRONEUSNICKNAME " ";
	reply += user.get_nickname();
	reply += " ";
	reply += nickname;
	reply += " :Erroneous nickname\r\n";
	return ( reply );
}

std::string const rpl::err_nicknametoolong( User & user, std::string nickname )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_ERRONEUSNICKNAME " ";
	reply += user.get_nickname();
	reply += " ";
	reply += nickname;
	reply += " :Nickname too long, max. 9 characters\r\n";
	return ( reply );
}

/* Returned when a NICK message is processed that results */
/* in an attempt to change to a currently existing */
/* nickname. */
std::string const rpl::err_nicknameinuse( User & user, std::string nickname )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NICKNAMEINUSE " ";
	reply += user.get_nickname();
	reply += " ";
	reply += nickname;
	reply += " :Nickname is already in use\r\n";
	return ( reply );
}

/* - Returned by a server to a user trying to join a channel */
/*   currently blocked by the channel delay mechanism. */
/* - Returned by a server to a user trying to change nickname */
/*   when the desired nickname is blocked by the nick delay */
/*   mechanism. */
std::string const rpl::err_unavailresource( User & user,
        std::string nickname_or_channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_UNAVAILRESOURCE " ";
	reply += user.get_nickname();
	reply += " ";
	reply += nickname_or_channel;
	reply += " :Nick/channel is temporarily unavailable\r\n";
	return ( reply );
}

/* Returned by the server to indicate that the target */
/* user of the command is not on the given channel. */
std::string const rpl::err_usernotinchannel( User & user, std::string nickname,
        std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_USERNOTINCHANNEL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += nickname;
	reply += " ";
	reply += channel;
	reply += " :They aren't on that channel\r\n";
	return ( reply );
}

/* Returned by the server whenever a client tries to */
/* perform a channel affecting command for which the */
/* client isn't a member. */
std::string const rpl::err_notonchannel( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOTONCHANNEL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :You're not on that channel\r\n";
	return ( reply );
}

/* Returned when a client tries to invite a user to a */
/* channel they are already on. */
std::string const rpl::err_useronchannel( User & user, std::string username,
        std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_USERONCHANNEL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += username;
	reply += " ";
	reply += channel;
	reply += " :is already on channel\r\n";
	return ( reply );
}

/* Returned by the summon after a SUMMON command for a */
/* user was unable to be performed since they were not */
/* logged in. */
std::string const rpl::err_nologin( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOLOGIN " ";
	reply += user.get_nickname();
	reply += " :User not logged in\r\n";
	return ( reply );
}

/* Returned as a response to the SUMMON command.  MUST be */
/* returned by any server which doesn't implement it. */
std::string const rpl::err_summondisabled( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_SUMMONDISABLED " ";
	reply += user.get_nickname();
	reply += " :SUMMON has been disabled\r\n";
	return ( reply );
}

/* Returned as a response to the USERS command.  MUST be */
/* returned by any server which does not implement it. */
std::string const rpl::err_usersdisabled( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_USERSDISABLED " ";
	reply += user.get_nickname();
	reply += " :USERS has been disabled\r\n";
	return ( reply );
}

/* Returned by the server to indicate that the client */
/* MUST be registered before the server will allow it */
/* to be parsed in detail. */
std::string const rpl::err_notregistered( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOTREGISTERED " ";
	reply += user.get_nickname();
	reply += " :You have not registered\r\n";
	return ( reply );
}

/* Returned by the server by numerous commands to */
/* indicate to the client that it didn't supply enough */
/* parameters. */
std::string const rpl::err_needmoreparams( User & user, std::string command )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NEEDMOREPARAMS " ";
	reply += user.get_nickname();
	reply += " ";
	reply += command;
	reply += " :Not enough parameters\r\n";
	return ( reply );
}

std::string const rpl::err_toomanyparams( User & user, std::string command )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NEEDMOREPARAMS " ";
	reply += user.get_nickname();
	reply += " ";
	reply += command;
	reply += " :Too many parameters\r\n";
	return ( reply );
}

/* Returned by the server to any link which tries to */
/* change part of the registered details (such as */
/* password or user details from second USER message). */
std::string const rpl::err_alreadyregistred( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_ALREADYREGISTRED " ";
	reply += user.get_nickname();
	reply += " :Unauthorized command (already registered)\r\n";
	return ( reply );
}

/* Returned to a client which attempts to register with */
/* a server which does not been setup to allow */
/* connections from the host the attempted connection */
/* is tried. */
std::string const rpl::err_nopermforhost( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOPERMFORHOST " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :Your host isn't among the privileged\r\n";
	return ( reply );
}

/* Returned to indicate a failed attempt at registering */
/* a connection for which a password was required and */
/* was either not given or incorrect. */
std::string const rpl::err_passwdmismatch( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_PASSWDMISMATCH " ";
	reply += user.get_nickname();
	reply += " :Password incorrect\r\n";
	return ( reply );
}

/* Returned after an attempt to connect and register */
/* yourself with a server which has been setup to */
/* explicitly deny connections to you. */
std::string const rpl::err_yourebannedcreep( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_YOUREBANNEDCREEP " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :You are banned from this server\r\n";
	return ( reply );
}

/* Sent by a server to a user to inform that access to the */
/* server will soon be denied. */
std::string const rpl::err_youwillbebanned( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_YOUWILLBEBANNED " ";
	reply += user.get_nickname();
	reply += " ";
	reply += "\r\n";
	return ( reply );
}

std::string const rpl::err_keyset( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_KEYSET " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :Channel key already set\r\n";
	return ( reply );
}

std::string const rpl::err_channelisfull( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_CHANNELISFULL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :Cannot join channel (+l)\r\n";
	return ( reply );
}

std::string const rpl::err_unknownmode( User & user, std::string channel,
                                        char modechar )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_UNKNOWNMODE " ";
	reply += user.get_nickname();
	reply += " ";
	reply += modechar;
	reply += " :is unknown mode char for ";
	reply += channel;
	reply += " \r\n";
	return ( reply );
}

std::string const rpl::err_inviteonlychan( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_INVITEONLYCHAN " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :Cannot join channel (+i)\r\n";
	return ( reply );
}

std::string const rpl::err_bannedfromchan( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_BANNEDFROMCHAN " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :Cannot join channel (+b)\r\n";
	return ( reply );
}

std::string const rpl::err_badchannelkey( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_BADCHANNELKEY " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :Cannot join channel (+k)\r\n";
	return ( reply );
}

std::string const rpl::err_badchanmask( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_BADCHANMASK " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :Bad Channel Mask\r\n";
	return ( reply );
}

std::string const rpl::err_nochanmodes( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOCHANMODES " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :Channel doesn't support modes\r\n";
	return ( reply );
}

std::string const rpl::err_banlistfull( User & user, std::string channel,
                                        std::string modechar )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_BANLISTFULL " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " ";
	reply += modechar;
	reply += " :Channel list is full\r\n";
	return ( reply );
}

/* Any command requiring operator privileges to operate */
/* MUST return this error to indicate the attempt was */
/* unsuccessful. */
std::string const rpl::err_noprivileges( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOPRIVILEGES " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :Permission Denied- You're not an IRC operator\r\n";
	return ( reply );
}

/* Any command requiring 'chanop' privileges (such as */
/* MODE messages) MUST return this error if the client */
/* making the attempt is not a chanop on the specified */
/* channel. */
std::string const rpl::err_chanoprivsneeded( User & user, std::string channel )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_CHANOPRIVSNEEDED " ";
	reply += user.get_nickname();
	reply += " ";
	reply += channel;
	reply += " :You're not channel operator\r\n";
	return ( reply );
}

/* Any attempts to use the KILL command on a server */
/* are to be refused and this error returned directly */
/* to the client. */
std::string const rpl::err_cantkillserver( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_CANTKILLSERVER " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :You can't kill a server!\r\n";
	return ( reply );
}

/* Sent by the server to a user upon connection to indicate */
/* the restricted nature of the connection (user mode "+r"). */
std::string const rpl::err_restricted( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_RESTRICTED " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :Your connection is restricted!\r\n";
	return ( reply );
}

/* Any MODE requiring "channel creator" privileges MUST */
/* return this error if the client making the attempt is not */
/* a chanop on the specified channel. */
std::string const rpl::err_uniqopprivsneeded( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_UNIQOPPRIVSNEEDED " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :You're not the original channel operator\r\n";
	return ( reply );
}

/* If a client sends an OPER message and the server has */
/* not been configured to allow connections from the */
/* client's host as an operator, this error MUST be */
/* returned. */
std::string const rpl::err_nooperhost( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_NOOPERHOST " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :No O-lines for your host\r\n";
	return ( reply );
}

/* Returned by the server to indicate that a MODE */
/* message was sent with a nickname parameter and that */
/* the a mode flag sent was not recognized. */
std::string const rpl::err_umodeunknownflag( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_UMODEUNKNOWNFLAG " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :Unknown MODE flag\r\n";
	return ( reply );
}

/* Error sent to any user trying to view or change the */
/* user mode for a user other than themselves. */
std::string const rpl::err_usersdontmatch( User & user )
{
	std::string reply = SERVER_PREFIX " ";
	reply += ERR_USERSDONTMATCH " ";
	reply += user.get_nickname();
	reply += " ";
	reply += " :Cannot change mode for other users\r\n";
	return ( reply );
}

std::string const rpl::err_generic( std::string msg )
{
	std::string reply = "ERROR :";
	reply += msg;
	reply += "\r\n";
	return ( reply );
}
