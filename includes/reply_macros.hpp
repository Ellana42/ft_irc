#ifndef REPLY_HPP
# define REPLY_HPP

/* NOTE: These codes are from the official rfc2812 documentation : */
/* https://www.rfc-editor.org/rfc/rfc2812#section-5 */

/* NOTE: These numeric replies might not all be implemented in ft_irc. */
/* Every numeric reply has an associated string, which will for the most part */
/* need to be reimplemented to replace placeholders. The ones defined here */
/* will either be modified or removed in the future. */

/* TODO: remove non-implemented replies. */

/* The following is a list of numeric replies which are generated in */
/* response to commands.  Each numeric is given with its */
/* number, name and reply string. */



/* Command responses */

/* Numerics in the range from 001 to 099 are used for client-server */
/* connections only and should never travel between servers.  Replies */
/* generated in the response to commands are found in the range from 200 */
/* to 399. */

# define RPL_WELCOME "001"
# define RPL_YOURHOST "002"
# define RPL_CREATED "003"
# define RPL_MYINFO "004"

# define RPL_BOUNCE "005"
# define RPL_BOUNCE_MSG "Try server <server name>, port <port number>"

# define RPL_USERHOST "302"
# define RPL_USERHOST_MSG ":*1<reply> *( " " <reply> )"
/* Reply format used by USERHOST to list replies to */
/* the query list.  The reply string is composed as */
/* follows: */
/*     reply = nickname [ "*" ] "=" ( "+" / "-" ) hostname */
/* The '*' indicates whether the client has registered */
/* as an Operator.  The '-' or '+' characters represent */
/* whether the client has set an AWAY message or not */
/* respectively. */

# define RPL_ISON "303"
# define RPL_ISON_MSG ":*1<nick> *( " " <nick> )"
/* Reply format used by ISON to list replies to the */
/* query list. */

# define RPL_AWAY "301"
# define RPL_AWAY_MSG "<nick> :<away message>"
# define RPL_UNAWAY "305"
# define RPL_UNAWAY_MSG ":You are no longer marked as being away"
# define RPL_NOAWAY "306"
# define RPL_NOAWAY_MSG ":You have been marked as being away"
/* These replies are used with the AWAY command (if */
/* allowed).  RPL_AWAY is sent to any client sending a */
/* PRIVMSG to a client which is away.  RPL_AWAY is only */
/* sent by the server to which the client is connected. */
/* Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the */
/* client removes and sets an AWAY message. */

# define RPL_WHOISUSER "311"
# define RPL_WHOISUSER_MSG "<nick> <user> <host> * :<real name>"
# define RPL_WHOISSERVER "312"
# define RPL_WHOISSERVER_MSG "<nick> <server> :<server info>"
# define RPL_WHOISOPERATOR "313"
# define RPL_WWHOISOPERATOR "<nick> :is an IRC operator"
# define RPL_WHOISIDLE "317"
# define RPL_WHOISIDLE_MSG "<nick> <integer> :seconds idle"
# define RPL_ENDOFWHOIS "318"
# define RPL_ENDOFWHOIS_MSG "<nick> :End of WHOIS list"
# define RPL_WHOISCHANNELS "319"
# define RPL_WHOISCHANNELS_MSG "<nick> :*( ( "@" / "+" ) <channel> " " )"
/* Replies 311 - 313, 317 - 319 are all replies */
/* generated in response to a WHOIS message.  Given that */
/* there are enough parameters present, the answering */
/* server MUST either formulate a reply out of the above */
/* numerics (if the query nick is found) or return an */
/* error reply.  The '*' in RPL_WHOISUSER is there as */
/* the literal character and not as a wild card.  For */
/* each reply set, only RPL_WHOISCHANNELS may appear */
/* more than once (for long lists of channel names). */
/* The '@' and '+' characters next to the channel name */
/* indicate whether a client is a channel operator or */
/* has been granted permission to speak on a moderated */
/* channel.  The RPL_ENDOFWHOIS reply is used to mark */
/* the end of processing a WHOIS message. */

# define RPL_WHOWASUSER "314"
# define RPL_WHOWASUSER_MSG "<nick> <user> <host> * :<real name>"
# define RPL_ENDOFWHOWAS "369"
# define RPL_ENDOFWHOWAS_MSG "<nick> :End of WHOWAS"
/* When replying to a WHOWAS message, a server MUST use */
/* the replies RPL_WHOWASUSER, RPL_WHOISSERVER or */
/* ERR_WASNOSUCHNICK for each nickname in the presented */
/* list.  At the end of all reply batches, there MUST */
/* be RPL_ENDOFWHOWAS (even if there was only one reply */
/* and it was an error). */

# define RPL_LIST "322"
# define RPL_LIST_MSG "<channel> <# visible> :<topic>"
# define RPL_LISTEND "323"
# define RPL_LISTEND_MSG ":End of LIST"
/* Replies RPL_LIST, RPL_LISTEND mark the actual replies */
/* with data and end of the server's response to a LIST */
/* command.  If there are no channels available to return, */
/* only the end reply MUST be sent. */

# define RPL_UNIQOPIS "325"
# define RPL_UNIQOPIS_MSG "<channel> <nickname>"
# define RPL_CHANNELMODEIS "324"
# define RPL_CHANNELMODEIS_MSG "<channel> <mode> <mode params>"

# define RPL_NOTOPIC "331"
# define RPL_NOTOPIC_MSG "<channel> :No topic is set"
# define RPL_TOPIC "332"
# define RPL_TOPIC_MSG "<channel> :<topic>"
/* When sending a TOPIC message to determine the */
/* channel topic, one of two replies is sent.  If */
/* the topic is set, RPL_TOPIC is sent back else */
/* RPL_NOTOPIC. */

# define RPL_INVITING "341"
# define RPL_INVITING_MSG "<channel> <nick>"
/* Returned by the server to indicate that the */
/* attempted INVITE message was successful and is */
/* being passed onto the end client. */

# define RPL_SUMMONING "342"
# define RPL_SUMMONING_MSG "<user> :Summoning user to IRC"
/* Returned by a server answering a SUMMON message to */
/* indicate that it is summoning that user. */

# define RPL_INVITELIST "346"
# define RPL_INVITELIST_MSG "<channel> <invitemask>"
# define RPL_ENDOFINVITELIST "347"
# define RPL_ENDOFINVITELIST_MSG "<channel> :End of channel invite list"
/* When listing the 'invitations masks' for a given channel, */
/* a server is required to send the list back using the */
/* RPL_INVITELIST and RPL_ENDOFINVITELIST messages.  A */
/* separate RPL_INVITELIST is sent for each active mask. */
/* After the masks have been listed (or if none present) a */
/* RPL_ENDOFINVITELIST MUST be sent. */

# define RPL_EXCEPTLIST "348"
# define RPL_EXCEPTLIST_MSG "<channel> <exceptionmask>"
# define RPL_ENDOFEXCEPTLIST "349"
# define RPL_ENDOFEXCEPTLIST_MSG "<channel> :End of channel exception list"
/* When listing the 'exception masks' for a given channel, */
/* a server is required to send the list back using the */
/* RPL_EXCEPTLIST and RPL_ENDOFEXCEPTLIST messages.  A */
/* separate RPL_EXCEPTLIST is sent for each active mask. */
/* After the masks have been listed (or if none present) */
/* a RPL_ENDOFEXCEPTLIST MUST be sent. */

# define RPL_VERSION "351"
# define RPL_VERSION_MSG "<version>.<debuglevel> <server> :<comments>"
/* Reply by the server showing its version details. */
/* The <version> is the version of the software being */
/* used (including any patchlevel revisions) and the */
/* <debuglevel> is used to indicate if the server is */
/* running in "debug mode". */
/* The "comments" field may contain any comments about */
/* the version or further version details. */

# define RPL_WHOREPLY "352"
# define RPL_WHOREPLY_MSG "<channel> <user> <host> <server> <nick> ( "H" / "G" > ["*"] [ ( "@" / "+" ) ] :<hopcount> <real name>"
# define RPL_ENDOFWHO "315"
# define RPL_ENDOFWHO_MSG "<name> :End of WHO list"
/* The RPL_WHOREPLY and RPL_ENDOFWHO pair are used */
/* to answer a WHO message.  The RPL_WHOREPLY is only */
/* sent if there is an appropriate match to the WHO */
/* query.  If there is a list of parameters supplied */
/* with a WHO message, a RPL_ENDOFWHO MUST be sent */
/* after processing each list item with <name> being */
/* the item. */

# define RPL_NAMREPLY "353"
# define RPL_NAMREPLY_MSG "( "=" / "*" / "@" ) <channel> :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )"
/* "@" is used for secret channels, "*" for private */
/* channels, and "=" for others (public channels). */

# define RPL_ENDOFNAMES "366"
# define RPL_ENDOFNAMES_MSG "<channel> :End of NAMES list"
/* To reply to a NAMES message, a reply pair consisting */
/* of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the */
/* server back to the client.  If there is no channel */
/* found as in the query, then only RPL_ENDOFNAMES is */
/* returned.  The exception to this is when a NAMES */
/* message is sent with no parameters and all visible */
/* channels and contents are sent back in a series of */
/* RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark */
/* the end. */

# define RPL_LINKS "364"
# define RPL_LINKS_MSG "<mask> <server> :<hopcount> <server info>"
# define RPL_ENDOFLINKS "365"
# define RPL_ENDOFLINKS_MSG "<mask> :End of LINKS list"
/* In replying to the LINKS message, a server MUST send */
/* replies back using the RPL_LINKS numeric and mark the */
/* end of the list using an RPL_ENDOFLINKS reply. */

# define RPL_BANLIST "367"
# define RPL_BANLIST_MSG "<channel> <banmask>"
# define RPL_ENDOFBANLIST "368"
# define RPL_ENDOFBANLIST_MSG "<channel> :End of channel ban list"
/* When listing the active 'bans' for a given channel, */
/* a server is required to send the list back using the */
/* RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate */
/* RPL_BANLIST is sent for each active banmask.  After the */
/* banmasks have been listed (or if none present) a */
/* RPL_ENDOFBANLIST MUST be sent. */

# define RPL_INFO "371"
# define RPL_ENDOFINFO "374"

# define RPL_MOTDSTART "375"
# define RPL_MOTDSTART_MSG ":- <server> Message of the day - "
# define RPL_MOTD "372"
# define RPL_MOTD_MSG ":- <text>"
# define RPL_ENDOFMOTD "376"
# define RPL_ENDOFMOTD_MSG ":End of MOTD command"
/* When responding to the MOTD message and the MOTD file */
/* is found, the file is displayed line by line, with */
/* each line no longer than 80 characters, using */
/* RPL_MOTD format replies.  These MUST be surrounded */
/* by a RPL_MOTDSTART (before the RPL_MOTDs) and an */
/* RPL_ENDOFMOTD (after). */

# define RPL_YOUREOPER "381"
# define RPL_YOUREOPER_MSG ":You are now an IRC operator"
/* RPL_YOUREOPER is sent back to a client which has */
/* just successfully issued an OPER message and gained */
/* operator status. */

# define RPL_REHASHING "382"
# define RPL_REHASHING_MSG "<config file> :Rehashing"
/* If the REHASH option is used and an operator sends */
/* a REHASH message, an RPL_REHASHING is sent back to */
/* the operator. */

# define RPL_YOURESERVICE "383"
# define RPL_YOURESERVICE_MSG "You are service <servicename>"
/* Sent by the server to a service upon successful */
/* registration. */

# define RPL_TIME "391"
# define RPL_TIME_MSG "<server> :<string showing server's local time>"
/* When replying to the TIME message, a server MUST send */
/* the reply using the RPL_TIME format above.  The string */
/* showing the time need only contain the correct day and */
/* time there.  There is no further requirement for the */
/* time string. */

# define RPL_USERSSTART "392"
# define RPL_USERSSTART_MSG ":UserID   Terminal  Host"
# define RPL_USERS "393"
# define RPL_USERS_MSG ":<username> <ttyline> <hostname>"
# define RPL_ENDOFUSERS "394"
# define RPL_ENDOFUSERS_MSG ":End of users"
# define RPL_NOUSERS "395"
# define RPL_NOUSERS_MSG ":Nobody logged in"
/* If the USERS message is handled by a server, the */
/* replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and */
/* RPL_NOUSERS are used.  RPL_USERSSTART MUST be sent */
/* first, following by either a sequence of RPL_USERS */
/* or a single RPL_NOUSER.  Following this is */
/* RPL_ENDOFUSERS. */

# define RPL_TRACELINK "200"
# define RPL_TRACELINK_MSG "Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>"
# define RPL_TRACECONNECTING "201"
# define RPL_TRACECONNECTING_MSG "Try. <class> <server>"
# define RPL_TRACEHANDSHAKE "202"
# define RPL_TRACEHANDSHAKE_MSG "H.S. <class> <server>"
# define RPL_TRACEUNKNOWN "203"
# define RPL_TRACEUNKNOWN_MSG "???? <class> [<client IP address in dot form>]"
# define RPL_TRACEOPERATOR "204"
# define RPL_TRACEOPERATOR_MSG "Oper <class> <nick>"
# define RPL_TRACEUSER "205"
# define RPL_TRACEUSER_MSG "User <class> <nick>"
# define RPL_TRACESERVER "206"
# define RPL_TRACESERVER_MSG "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>"
# define RPL_TRACESERVICE  "207"
# define RPL_TRACESERVICE_MSG "Service <class> <name> <type> <active type>"
# define RPL_TRACENEWTYPE "208"
# define RPL_TRACENEWTYPE_MSG "<newtype> 0 <client name>"
# define RPL_TRACECLASS "209"
# define RPL_TRACECLASS_MSG "Class <class> <count>"
# define RPL_TRACELOG "261"
# define RPL_TRACELOG_MSG "File <logfile> <debug level>"
# define RPL_TRACEEND "262"
# define RPL_TRACEEND_MSG "<server name> <version & debug level> :End of TRACE"
/* The RPL_TRACE* are all returned by the server in */
/* response to the TRACE message.  How many are */
/* returned is dependent on the TRACE message and */
/* whether it was sent by an operator or not.  There */
/* is no predefined order for which occurs first. */
/* Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and */
/* RPL_TRACEHANDSHAKE are all used for connections */
/* which have not been fully established and are either */
/* unknown, still attempting to connect or in the */
/* process of completing the 'server handshake'. */
/* RPL_TRACELINK is sent by any server which handles */
/* a TRACE message and has to pass it on to another */
/* server.  The list of RPL_TRACELINKs sent in */
/* response to a TRACE command traversing the IRC */
/* network should reflect the actual connectivity of */
/* the servers themselves along that path. */
/* RPL_TRACENEWTYPE is to be used for any connection */
/* which does not fit in the other categories but is */
/* being displayed anyway. */
/* RPL_TRACEEND is sent to indicate the end of the list. */

# define RPL_STATSLINKINFO "211"
# define RPL_STATSLINKINFO_MSG "<linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>"
/* reports statistics on a connection.  <linkname> */
/* identifies the particular connection, <sendq> is */
/* the amount of data that is queued and waiting to be */
/* sent <sent messages> the number of messages sent, */
/* and <sent Kbytes> the amount of data sent, in */
/* Kbytes. <received messages> and <received Kbytes> */
/* are the equivalent of <sent messages> and <sent */
/* Kbytes> for received data, respectively.  <time */
/* open> indicates how long ago the connection was */
/* opened, in seconds. */

# define RPL_STATSCOMMANDS "212"
# define RPL_STATSCOMMANDS_MSG "<command> <count> <byte count> <remote count>"
/* reports statistics on commands usage. */

# define RPL_ENDOFSTATS "219"
# define RPL_ENDOFSTATS_MSG "<stats letter> :End of STATS report"

# define RPL_STATSUPTIME "242"
# define RPL_STATSUPTIME_MSG ":Server Up %d days %d:%02d:%02d"
/* reports the server uptime. */

# define RPL_STATSOLINE "243"
# define RPL_STATSOLINE_MSG "O <hostmask> * <name>"
/* reports the allowed hosts from where user may become IRC */
/* operators. */

# define RPL_UMODEIS "221"
# define RPL_UMODEIS_MSG "<user mode string>"
/* To answer a query about a client's own mode, */
/* RPL_UMODEIS is sent back. */

# define RPL_SERVLIST "234"
# define RPL_SERVLIST_MSG "<name> <server> <mask> <type> <hopcount> <info>"
# define RPL_SERVLISTEND "235"
# define RPL_SERVLISTEND_MSG "<mask> <type> :End of service listing"
/* When listing services in reply to a SERVLIST message, */
/* a server is required to send the list back using the */
/* RPL_SERVLIST and RPL_SERVLISTEND messages.  A separate */
/* RPL_SERVLIST is sent for each service.  After the */
/* services have been listed (or if none present) a */
/* RPL_SERVLISTEND MUST be sent. */

# define RPL_LUSERCLIENT "251"
# define RPL_LUSERCLIENT_MSG ":There are <integer> users and <integer> services on <integer> servers"
# define RPL_LUSEROP "252"
# define RPL_LUSEROP_MSG "<integer> :operator(s) online"
# define RPL_LUSERUNKNOWN "253"
# define RPL_LUSERUNKNOWN_MSG "<integer> :unknown connection(s)"
# define RPL_LUSERCHANNELS "254"
# define RPL_LUSERCHANNELS_MSG "<integer> :channels formed"
# define RPL_LUSERME "255"
# define RPL_LUSERME_MSG ":I have <integer> clients and <integer> servers"
/* In processing an LUSERS message, the server */
/* sends a set of replies from RPL_LUSERCLIENT, */
/* RPL_LUSEROP, RPL_USERUNKNOWN, */
/* RPL_LUSERCHANNELS and RPL_LUSERME.  When */
/* replying, a server MUST send back */
/* RPL_LUSERCLIENT and RPL_LUSERME.  The other */
/* replies are only sent back if a non-zero count */
/* is found for them. */

# define RPL_ADMINME "256"
# define RPL_ADMINLOC1 "257"
# define RPL_ADMINLOC2 "258"
# define RPL_ADMINEMAIL "259"

# define RPL_TRYAGAIN "263"
# define RPL_TRYAGAIN_MSG "<command> :Please wait a while and try again."
/* When a server drops a command without processing it, */
/* it MUST use the reply RPL_TRYAGAIN to inform the */
/* originating client. */


/* The following are in current use but are part of a non-generic 'feature' of */
/* the current IRC server. */
# define RPL_SERVICEINFO "231"
# define RPL_ENDOFSERVICES "232"
# define RPL_SERVICE "233"
# define RPL_NONE "300"
# define RPL_WHOISCHANOP "316"
# define RPL_KILLDONE "361"
# define RPL_CLOSING "362"
# define RPL_CLOSEEND "363"
# define RPL_INFOSTART "373"
# define RPL_MYPORTIS "384"
# define RPL_STATSCLINE "213"
# define RPL_STATSNLINE "214"
# define RPL_STATSILINE "215"
# define RPL_STATSKLINE "216"
# define RPL_STATSQLINE "217"
# define RPL_STATSYLINE "218"
# define RPL_STATSVLINE "240"
# define RPL_STATSLLINE "241"
# define RPL_STATSHLINE "244"
# define RPL_STATSSLINE "244"
# define RPL_STATSPING "246"
# define RPL_STATSBLINE "247"
# define RPL_STATSDLINE "250"


#endif
