#ifndef REPLY_HPP
#define REPLY_HPP

#include "reply_macros.hpp"
#include "reply_macros_error.hpp"
#include "ft_irc.hpp"
#include "User.hpp"
#include "Message.hpp"
#include "Channel.hpp"

namespace rpl
{
std::string const welcome( User & user );
std::string const yourhost( User & user );
std::string const created( User & user );
std::string const myinfo( User & user );
std::string const server_version( User & user );
std::string const adminme( User & user );
std::string const adminloc1( User & user );
std::string const adminloc2( User & user );
std::string const adminemail( User & user );
std::string const info( User & user, int line );
std::string const info_end( User & user );
std::string const confirmation( std::string const identifier,
                                Message & message );
std::string const join_channel( User & user, Channel & channel );
std::string const mode_channel( User & user, Channel & channel,
                                std::string mode );
std::string const namreply( User & user, Channel & channel );
std::string const endofnames( User & user, std::string chan_name );
std::string const part( User & user, Channel & channel, Message & message );
std::string const create_part_message( Channel & channel );
std::string const quit( User & user, Message & message );

std::string const forward( User & sender, Message & message );

std::string const err_nosuchnick( User & user, std::string name_or_channel );
std::string const err_nosuchnick( User & user, std::string name_or_channel );
std::string const err_nosuchserver( User & user, std::string server_name );
std::string const err_nosuchchannel( User & user, std::string channel_name );
std::string const err_cannotsendtochan( User & user, std::string channel_name );
std::string const err_toomanychannels( User & user, std::string channel_name );
std::string const err_wasnosuchnick( User & user, std::string nickname );
std::string const err_toomanytargets( User & user, std::string target,
                                      int error_code,
                                      std::string abort_message );
std::string const err_nosuchservice( User & user, std::string service_name );
std::string const err_noorigin( User & user );
std::string const err_norecipient( User & user, std::string command );
std::string const err_notexttosend( User & user );
std::string const err_notoplevel( User & user, std::string mask );
std::string const err_wildtoplevel( User & user, std::string mask );
std::string const err_badmask( User & user, std::string mask );
std::string const err_unknowncommand( User & user, std::string command );
std::string const err_nomotd( User & user );
std::string const err_noadmininfo( User & user, std::string server );
std::string const err_fileerror( User & user, std::string file_operation,
                                 std::string filename );
std::string const err_nonicknamegiven( User & user );
std::string const err_erroneusnickname( User & user, std::string nickname );
std::string const err_nicknametoolong( User & user, std::string nickname );
std::string const err_nicknameinuse( User & user, std::string nickname );
std::string const err_unavailresource( User & user,
                                       std::string nickname_or_channel );
std::string const err_usernotinchannel( User & user, std::string nickname,
                                        std::string channel );
std::string const err_notonchannel( User & user, std::string channel );
std::string const err_useronchannel( User & user, std::string username,
                                     std::string channel );
std::string const err_nologin( User & user );
std::string const err_summondisabled( User & user );
std::string const err_usersdisabled( User & user );
std::string const err_notregistered( User & user );
std::string const err_needmoreparams( User & user, std::string command );
std::string const err_toomanyparams( User & user, std::string command );
std::string const err_alreadyregistred( User & user );
std::string const err_nopermforhost( User & user );
std::string const err_passwdmismatch( User & user );
std::string const err_yourebannedcreep( User & user );
std::string const err_youwillbebanned( User & user );
std::string const err_keyset( User & user, std::string channel );
std::string const err_channelisfull( User & user, std::string channel );
std::string const err_unknownmode( User & user, std::string channel,
                                   char modechar );
std::string const err_inviteonlychan( User & user, std::string channel );
std::string const err_bannedfromchan( User & user, std::string channel );
std::string const err_badchannelkey( User & user, std::string channel );
std::string const err_badchanmask( User & user, std::string channel );
std::string const err_nochanmodes( User & user, std::string channel );
std::string const err_banlistfull( User & user, std::string channel,
                                   std::string modechar );
std::string const err_noprivileges( User & user );
std::string const err_chanoprivsneeded( User & user, std::string channel );
std::string const err_cantkillserver( User & user );
std::string const err_restricted( User & user );
std::string const err_uniqopprivsneeded( User & user );
std::string const err_nooperhost( User & user );
std::string const err_umodeunknownflag( User & user );
std::string const err_usersdontmatch( User & user );
std::string const err_invalidusername( void );
std::string const err_invalidmodestring( void );
std::string const err_generic( std::string msg );
std::string const liststart( User & user );
std::string const list( User & user, Channel & channel );
std::string const listend( User & user );
std::string const kick( User & sender, User & user, Channel & channel,
                        std::string comment );
std::string const inviting( User & user, Message & message );
std::string const invite( User & sender, Message & message );
std::string const pong( User & sender, Message & message );
std::string const notopic( Message & message, Channel & channel );
std::string const topic( Message & message, Channel & channel );
std::string const umodeis( Message & message, User & user );
std::string const channelmodeis( Message & message, Channel & channel );
std::string const newtopic( User & sender, Message & message );
std::string const ping( std::string token );
std::string const invalidmodeparam( User & sender, std::string channel_name,
                                    char mode_char, std::string description );
}

#endif
