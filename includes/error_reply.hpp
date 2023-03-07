#ifndef ERROR_REPLY_HPP
# define ERROR_REPLY_HPP

/* NOTE: These codes are from the official rfc2812 documentation : */
/* https://www.rfc-editor.org/rfc/rfc2812#section-5 */

/* NOTE: These numeric error replies might not all be implemented in ft_irc. */
/* Every numeric reply has an associated string, which will for the most part */
/* need to be reimplemented to replace placeholders. The ones defined here */
/* will either be modified or removed in the future. */

/* TODO: remove non-implemented replies. */

/* Error replies are found in the range from 400 to 599. */

# define ERR_NOSUCHNICK "401"
# define ERR_NOSUCHNICK_MSG "<nickname> :No such nick/channel"
/* Used to indicate the nickname parameter supplied to a */
/* command is currently unused. */

# define ERR_NOSUCHSERVER "402"
# define ERR_NOSUCHSERVER_MSG "<server name> :No such server"
/* Used to indicate the server name given currently */
/* does not exist. */

# define ERR_NOSUCHCHANNEL "403"
# define ERR_NOSUCHCHANNEL_MSG "<channel name> :No such channel"
/* Used to indicate the given channel name is invalid. */

# define ERR_CANNOTSENDTOCHAN "404"
# define ERR_CANNOTSENDTOCHAN_MSG "<channel name> :Cannot send to channel"
/* Sent to a user who is either (a) not on a channel */
/* which is mode +n or (b) not a chanop (or mode +v) on */
/* a channel which has mode +m set or where the user is */
/* banned and is trying to send a PRIVMSG message to */
/* that channel. */

# define ERR_TOOMANYCHANNELS "405"
# define ERR_TOOMANYCHANNELS_MSG "<channel name> :You have joined too many channels"
/* Sent to a user when they have joined the maximum */
/* number of allowed channels and they try to join */
/* another channel. */

# define ERR_WASNOSUCHNICK "406"
# define ERR_WASNOSUCHNICK_MSG "<nickname> :There was no such nickname"
/* Returned by WHOWAS to indicate there is no history */
/* information for that nickname. */

# define ERR_TOOMANYTARGETS "407"
# define ERR_TOOMANYTARGETS_MSG "<target> :<error code> recipients. <abort message>"
/* - Returned to a client which is attempting to send a */
/*   PRIVMSG/NOTICE using the user@host destination format */
/*   and for a user@host which has several occurrences. */
/* - Returned to a client which trying to send a */
/*   PRIVMSG/NOTICE to too many recipients. */
/* - Returned to a client which is attempting to JOIN a safe */
/*   channel using the shortname when there are more than one */
/*   such channel. */

# define ERR_NOSUCHSERVICE "408"
# define ERR_NOSUCHSERVICE_MSG "<service name> :No such service"
/* Returned to a client which is attempting to send a SQUERY */
/* to a service which does not exist. */

# define ERR_NOORIGIN "409"
# define ERR_NOORIGIN_MSG ":No origin specified"
/* - PING or PONG message missing the originator parameter. */

# define ERR_NORECIPIENT "411"
# define ERR_NORECIPIENT_MSG ":No recipient given (<command>)"
# define ERR_NOTEXTTOSEND "412"
# define ERR_NOTEXTTOSEND_MSG ":No text to send"
# define ERR_NOTOPLEVEL "413"
# define ERR_NOTOPLEVEL_MSG "<mask> :No toplevel domain specified"
# define ERR_WILDTOPLEVEL "414"
# define ERR_WILDTOPLEVEL_MSG "<mask> :Wildcard in toplevel domain"
# define ERR_BADMASK "415"
# define ERR_BADMASK_MSG "<mask> :Bad Server/host mask"
/* 412 - 415 are returned by PRIVMSG to indicate that */
/* the message wasn't delivered for some reason. */
/* ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that */
/* are returned when an invalid use of */
/* "PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted. */

# define ERR_UNKNOWNCOMMAND "421"
# define ERR_UNKNOWNCOMMAND_MSG "<command> :Unknown command"
/* Returned to a registered client to indicate that the */
/* command sent is unknown by the server. */

# define ERR_NOMOTD "422"
# define ERR_NOMOTD_MSG ":MOTD File is missing"
/* Server's MOTD file could not be opened by the server. */

# define ERR_NOADMININFO "423"
# define ERR_NOADMININFO_MSG "<server> :No administrative info available"
/* Returned by a server in response to an ADMIN message */
/* when there is an error in finding the appropriate */
/* information. */

# define ERR_FILEERROR "424"
# define ERR_FILEERROR_MSG ":File error doing <file op> on <file>"
/* Generic error message used to report a failed file */
/* operation during the processing of a message. */

# define ERR_NONICKNAMEGIVEN "431"
# define ERR_NONICKNAMEGIVEN_MSG ":No nickname given"
/* Returned when a nickname parameter expected for a */
/* command and isn't found. */

# define ERR_ERRONEUSNICKNAME "432"
# define ERR_ERRONEUSNICKNAME_MSG "<nick> :Erroneous nickname"
/* Returned after receiving a NICK message which contains */
/* characters which do not fall in the defined set.  See */
/* section 2.3.1 for details on valid nicknames. */

# define ERR_NICKNAMEINUSE "433"
# define ERR_NICKNAMEINUSE_MSG "<nick> :Nickname is already in use"
/* Returned when a NICK message is processed that results */
/* in an attempt to change to a currently existing */
/* nickname. */

# define ERR_NICKCOLLISION "436"
# define ERR_NICKCOLLISION_MSG "<nick> :Nickname collision KILL from <user>@<host>"
/* Returned by a server to a client when it detects a */
/* nickname collision (registered of a NICK that */
/* already exists by another server). */

# define ERR_UNAVAILRESOURCE "437"
# define "<nick/channel> :Nick/channel is temporarily unavailable"
/* - Returned by a server to a user trying to join a channel */
/*   currently blocked by the channel delay mechanism. */
/* - Returned by a server to a user trying to change nickname */
/*   when the desired nickname is blocked by the nick delay */
/*   mechanism. */

# define ERR_USERNOTINCHANNEL "441"
# define ERR_USERNOTINCHANNEL_MSG "<nick> <channel> :They aren't on that channel"
/* Returned by the server to indicate that the target */
/* user of the command is not on the given channel. */

# define ERR_NOTONCHANNEL "442"
# define ERR_NOTONCHANNEL_MSG "<channel> :You're not on that channel"
/* Returned by the server whenever a client tries to */
/* perform a channel affecting command for which the */
/* client isn't a member. */

# define ERR_USERONCHANNEL "443"
# define ERR_USERONCHANNEL_MSG "<user> <channel> :is already on channel"
/* Returned when a client tries to invite a user to a */
/* channel they are already on. */

# define ERR_NOLOGIN "444"
# define ERR_NOLOGIN_MSG "<user> :User not logged in"
/* Returned by the summon after a SUMMON command for a */
/* user was unable to be performed since they were not */
/* logged in. */

# define ERR_SUMMONDISABLED "445"
# define ERR_SUMMONDISABLED_MSG ":SUMMON has been disabled"
/* Returned as a response to the SUMMON command.  MUST be */
/* returned by any server which doesn't implement it. */

# define ERR_USERSDISABLED "446"
# define ERR_USERSDISABLED_MSG ":USERS has been disabled"
/* Returned as a response to the USERS command.  MUST be */
/* returned by any server which does not implement it. */

# define ERR_NOTREGISTERED "451"
# define ERR_NOTREGISTERED_MSG ":You have not registered"
/* Returned by the server to indicate that the client */
/* MUST be registered before the server will allow it */
/* to be parsed in detail. */

# define ERR_NEEDMOREPARAMS "461"
# define ERR_NEEDMOREPARAMS_MSG "<command> :Not enough parameters"
/* Returned by the server by numerous commands to */
/* indicate to the client that it didn't supply enough */
/* parameters. */

# define ERR_ALREADYREGISTRED "462"
# define ERR_ALREADYREGISTRED_MSG ":Unauthorized command (already registered)"
/* Returned by the server to any link which tries to */
/* change part of the registered details (such as */
/* password or user details from second USER message). */

# define ERR_NOPERMFORHOST "463"
# define ERR_NOPERMFORHOST_MSG ":Your host isn't among the privileged"
/* Returned to a client which attempts to register with */
/* a server which does not been setup to allow */
/* connections from the host the attempted connection */
/* is tried. */

# define ERR_PASSWDMISMATCH "464"
# define ERR_PASSWDMISMATCH_MSG ":Password incorrect"
/* Returned to indicate a failed attempt at registering */
/* a connection for which a password was required and */
/* was either not given or incorrect. */

# define ERR_YOUREBANNEDCREEP "465"
# define ERR_YOUREBANNEDCREEP_MSG ":You are banned from this server"
/* Returned after an attempt to connect and register */
/* yourself with a server which has been setup to */
/* explicitly deny connections to you. */

# define ERR_YOUWILLBEBANNED "466"
# define ERR_YOUWILLBEBANNED_MSG ""
/* Sent by a server to a user to inform that access to the */
/* server will soon be denied. */

# define ERR_KEYSET "467"
# define ERR_KEYSET_MSG "<channel> :Channel key already set"
# define ERR_CHANNELISFULL "471"
# define ERR_CHANNELISFULL_MSG "<channel> :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE "472"
# define ERR_UNKNOWNMODE_MSG "<char> :is unknown mode char to me for <channel>"
# define ERR_INVITEONLYCHAN "473"
# define ERR_INVITEONLYCHAN_MSG "<channel> :Cannot join channel (+i)"
# define ERR_BANNEDFROMCHAN "474"
# define ERR_BANNEDFROMCHAN_MSG "<channel> :Cannot join channel (+b)"
# define ERR_BADCHANNELKEY "475"
# define ERR_BADCHANNELKEY_MSG "<channel> :Cannot join channel (+k)"
# define ERR_BADCHANMASK "476"
# define ERR_BADCHANMASK_MSG "<channel> :Bad Channel Mask"
# define ERR_NOCHANMODES "477"
# define ERR_NOCHANMODES_MSG "<channel> :Channel doesn't support modes"
# define ERR_BANLISTFULL "478"
# define ERR_BANLISTFULL_MSG "<channel> <char> :Channel list is full"

# define ERR_NOPRIVILEGES "481"
# define ERR_NOPRIVILEGES_MSG ":Permission Denied- You're not an IRC operator"
/* Any command requiring operator privileges to operate */
/* MUST return this error to indicate the attempt was */
/* unsuccessful. */

# define ERR_CHANOPRIVSNEEDED "482"
# define ERR_CHANOPRIVSNEEDED_MSG  "<channel> :You're not channel operator"
/* Any command requiring 'chanop' privileges (such as */
/* MODE messages) MUST return this error if the client */
/* making the attempt is not a chanop on the specified */
/* channel. */

# define ERR_CANTKILLSERVER "483"
# define ERR_CANTKILLSERVER_MSG ":You can't kill a server!"
/* Any attempts to use the KILL command on a server */
/* are to be refused and this error returned directly */
/* to the client. */

# define ERR_RESTRICTED "484"
# define ERR_RESTRICTED_MSG ":Your connection is restricted!"
/* Sent by the server to a user upon connection to indicate */
/* the restricted nature of the connection (user mode "+r"). */

# define ERR_UNIQOPPRIVSNEEDED "485"
# define ERR_UNIQOPPRIVSNEEDED_MSG ":You're not the original channel operator"
/* Any MODE requiring "channel creator" privileges MUST */
/* return this error if the client making the attempt is not */
/* a chanop on the specified channel. */

# define ERR_NOOPERHOST "491"
# define ERR_NOOPERHOST_MSG ":No O-lines for your host"
/* If a client sends an OPER message and the server has */
/* not been configured to allow connections from the */
/* client's host as an operator, this error MUST be */
/* returned. */

# define ERR_UMODEUNKNOWNFLAG "501"
# define ERR_UMODEUNKNOWNFLAG_MSG ":Unknown MODE flag"
/* Returned by the server to indicate that a MODE */
/* message was sent with a nickname parameter and that */
/* the a mode flag sent was not recognized. */

# define ERR_USERSDONTMATCH "502"
# define ERR_USERSDONTMATCH_MSG ":Cannot change mode for other users"
/* Error sent to any user trying to view or change the */
/* user mode for a user other than themselves. */

/* The following are in current use but are part of a non-generic 'feature' of */
/* the current IRC server. */
# define ERR_NOSERVICEHOST "492"

#endif
