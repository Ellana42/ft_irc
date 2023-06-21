#ifndef REPLY_MACROS_HPP
# define REPLY_MACROS_HPP

/* NOTE: These codes are from the official rfc2812 documentation : */
/* https://www.rfc-editor.org/rfc/rfc2812#section-5 */

/* NOTE: These numeric replies might not all be implemented in ft_irc. */

/* Command responses */

/* Numerics in the range from 001 to 099 are used for client-server */
/* connections only and should never travel between servers.  Replies */
/* generated in the response to commands are found in the range from 200 */
/* to 399. */

# define RPL_WELCOME "001"
# define RPL_YOURHOST "002"
# define RPL_CREATED "003"
# define RPL_MYINFO "004"

/* # define RPL_BOUNCE "005" */
/* # define RPL_USERHOST "302" */
/* # define RPL_ISON "303" */

/* These replies are used with the AWAY command (if */
/* allowed).  RPL_AWAY is sent to any client sending a */
/* PRIVMSG to a client which is away.  RPL_AWAY is only */
/* sent by the server to which the client is connected. */
/* Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the */
/* client removes and sets an AWAY message. */
# define RPL_AWAY "301"
# define RPL_UNAWAY "305"
# define RPL_NOAWAY "306"

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
# define RPL_WHOISUSER "311"
# define RPL_WHOISSERVER "312"
# define RPL_WHOISOPERATOR "313"
# define RPL_WHOISIDLE "317"
# define RPL_ENDOFWHOIS "318"
# define RPL_WHOISCHANNELS "319"

/* When replying to a WHOWAS message, a server MUST use */
/* the replies RPL_WHOWASUSER, RPL_WHOISSERVER or */
/* ERR_WASNOSUCHNICK for each nickname in the presented */
/* list.  At the end of all reply batches, there MUST */
/* be RPL_ENDOFWHOWAS (even if there was only one reply */
/* and it was an error). */
# define RPL_WHOWASUSER "314"
# define RPL_ENDOFWHOWAS "369"

/* Replies RPL_LIST, RPL_LISTEND mark the actual replies */
/* with data and end of the server's response to a LIST */
/* command.  If there are no channels available to return, */
/* only the end reply MUST be sent. */
# define RPL_LIST "322"
# define RPL_LISTEND "323"

# define RPL_UNIQOPIS "325"
# define RPL_CHANNELMODEIS "324"

/* When sending a TOPIC message to determine the */
/* channel topic, one of two replies is sent.  If */
/* the topic is set, RPL_TOPIC is sent back else */
/* RPL_NOTOPIC. */
# define RPL_NOTOPIC "331"
# define RPL_TOPIC "332"

/* Returned by the server to indicate that the */
/* attempted INVITE message was successful and is */
/* being passed onto the end client. */
# define RPL_INVITING "341"

/* Returned by a server answering a SUMMON message to */
/* indicate that it is summoning that user. */
# define RPL_SUMMONING "342"

/* When listing the 'invitations masks' for a given channel, */
/* a server is required to send the list back using the */
/* RPL_INVITELIST and RPL_ENDOFINVITELIST messages.  A */
/* separate RPL_INVITELIST is sent for each active mask. */
/* After the masks have been listed (or if none present) a */
/* RPL_ENDOFINVITELIST MUST be sent. */
# define RPL_INVITELIST "346"
# define RPL_ENDOFINVITELIST "347"

/* When listing the 'exception masks' for a given channel, */
/* a server is required to send the list back using the */
/* RPL_EXCEPTLIST and RPL_ENDOFEXCEPTLIST messages.  A */
/* separate RPL_EXCEPTLIST is sent for each active mask. */
/* After the masks have been listed (or if none present) */
/* a RPL_ENDOFEXCEPTLIST MUST be sent. */
# define RPL_EXCEPTLIST "348"
# define RPL_ENDOFEXCEPTLIST "349"

/* Reply by the server showing its version details. */
/* The <version> is the version of the software being */
/* used (including any patchlevel revisions) and the */
/* <debuglevel> is used to indicate if the server is */
/* running in "debug mode". */
/* The "comments" field may contain any comments about */
/* the version or further version details. */
# define RPL_VERSION "351"

/* The RPL_WHOREPLY and RPL_ENDOFWHO pair are used */
/* to answer a WHO message.  The RPL_WHOREPLY is only */
/* sent if there is an appropriate match to the WHO */
/* query.  If there is a list of parameters supplied */
/* with a WHO message, a RPL_ENDOFWHO MUST be sent */
/* after processing each list item with <name> being */
/* the item. */
# define RPL_WHOREPLY "352"
# define RPL_ENDOFWHO "315"

# define RPL_NAMREPLY "353"
# define RPL_ENDOFNAMES "366"

/* In replying to the LINKS message, a server MUST send */
/* replies back using the RPL_LINKS numeric and mark the */
/* end of the list using an RPL_ENDOFLINKS reply. */
# define RPL_LINKS "364"
# define RPL_ENDOFLINKS "365"

/* When listing the active 'bans' for a given channel, */
/* a server is required to send the list back using the */
/* RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate */
/* RPL_BANLIST is sent for each active banmask.  After the */
/* banmasks have been listed (or if none present) a */
/* RPL_ENDOFBANLIST MUST be sent. */
# define RPL_BANLIST "367"
# define RPL_ENDOFBANLIST "368"

# define RPL_INFO "371"
# define RPL_ENDOFINFO "374"

/* When responding to the MOTD message and the MOTD file */
/* is found, the file is displayed line by line, with */
/* each line no longer than 80 characters, using */
/* RPL_MOTD format replies.  These MUST be surrounded */
/* by a RPL_MOTDSTART (before the RPL_MOTDs) and an */
/* RPL_ENDOFMOTD (after). */
# define RPL_MOTDSTART "375"
# define RPL_MOTD "372"
# define RPL_ENDOFMOTD "376"

/* RPL_YOUREOPER is sent back to a client which has */
/* just successfully issued an OPER message and gained */
/* operator status. */
# define RPL_YOUREOPER "381"

/* If the REHASH option is used and an operator sends */
/* a REHASH message, an RPL_REHASHING is sent back to */
/* the operator. */
# define RPL_REHASHING "382"

/* Sent by the server to a service upon successful */
/* registration. */
# define RPL_YOURESERVICE "383"

/* When replying to the TIME message, a server MUST send */
/* the reply using the RPL_TIME format above.  The string */
/* showing the time need only contain the correct day and */
/* time there.  There is no further requirement for the */
/* time string. */
# define RPL_TIME "391"

/* If the USERS message is handled by a server, the */
/* replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and */
/* RPL_NOUSERS are used.  RPL_USERSSTART MUST be sent */
/* first, following by either a sequence of RPL_USERS */
/* or a single RPL_NOUSER.  Following this is */
/* RPL_ENDOFUSERS. */
# define RPL_USERSSTART "392"
# define RPL_USERS "393"
# define RPL_ENDOFUSERS "394"
# define RPL_NOUSERS "395"

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
# define RPL_TRACELINK "200"
# define RPL_TRACECONNECTING "201"
# define RPL_TRACEHANDSHAKE "202"
# define RPL_TRACEUNKNOWN "203"
# define RPL_TRACEOPERATOR "204"
# define RPL_TRACEUSER "205"
# define RPL_TRACESERVER "206"
# define RPL_TRACESERVICE  "207"
# define RPL_TRACENEWTYPE "208"
# define RPL_TRACECLASS "209"
# define RPL_TRACELOG "261"
# define RPL_TRACEEND "262"

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
# define RPL_STATSLINKINFO "211"
# define RPL_STATSCOMMANDS "212"
# define RPL_ENDOFSTATS "219"
# define RPL_STATSUPTIME "242"
# define RPL_STATSOLINE "243"

/* To answer a query about a client's own mode, */
/* RPL_UMODEIS is sent back. */
# define RPL_UMODEIS "221"

/* When listing services in reply to a SERVLIST message, */
/* a server is required to send the list back using the */
/* RPL_SERVLIST and RPL_SERVLISTEND messages.  A separate */
/* RPL_SERVLIST is sent for each service.  After the */
/* services have been listed (or if none present) a */
/* RPL_SERVLISTEND MUST be sent. */
# define RPL_SERVLIST "234"
# define RPL_SERVLISTEND "235"

/* In processing an LUSERS message, the server */
/* sends a set of replies from RPL_LUSERCLIENT, */
/* RPL_LUSEROP, RPL_USERUNKNOWN, */
/* RPL_LUSERCHANNELS and RPL_LUSERME.  When */
/* replying, a server MUST send back */
/* RPL_LUSERCLIENT and RPL_LUSERME.  The other */
/* replies are only sent back if a non-zero count */
/* is found for them. */
# define RPL_LUSERCLIENT "251"
# define RPL_LUSEROP "252"
# define RPL_LUSERUNKNOWN "253"
# define RPL_LUSERCHANNELS "254"
# define RPL_LUSERME "255"

# define RPL_ADMINME "256"
# define RPL_ADMINLOC1 "257"
# define RPL_ADMINLOC2 "258"
# define RPL_ADMINEMAIL "259"

/* When a server drops a command without processing it, */
/* it MUST use the reply RPL_TRYAGAIN to inform the */
/* originating client. */
# define RPL_TRYAGAIN "263"


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
# define RPL_INVALIDMODEPARAM "696"

#endif
