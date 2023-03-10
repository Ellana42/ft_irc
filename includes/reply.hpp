#include "reply_macros.hpp"
#include "reply_macros_error.hpp"
#include "ft_irc.hpp"
#include "User.hpp"
#include "Message.hpp"

namespace rpl
{
std::string const welcome( User & User );
std::string const yourhost( void );
std::string const created( void );
std::string const myinfo( void );

std::string const forward( User sender, Message message );

std::string const err_nosuchnick( std::string name_or_channel );
std::string const err_nosuchnick( std::string name_or_channel );
std::string const err_nosuchserver( std::string server_name );
std::string const err_nosuchchannel( std::string channel_name );
std::string const err_cannotsendtochan( std::string channel_name );
std::string const err_toomanychannels( std::string channel_name );
std::string const err_wasnosuchnick( std::string nickname );
std::string const err_toomanytargets( std::string target, int error_code,
                                      std::string abort_message );
std::string const err_nosuchservice( std::string service_name );
std::string const err_noorigin( void );
std::string const err_norecipient( std::string command );
std::string const err_notexttosend( void );
std::string const err_notoplevel( std::string mask );
std::string const err_wildtoplevel( std::string mask );
std::string const err_badmask( std::string mask );
std::string const err_unknowncommand( std::string command );
std::string const err_nomotd( void );
std::string const err_noadmininfo( std::string server );
std::string const err_fileerror( std::string file_operation,
                                 std::string filename );
std::string const err_nonicknamegiven( void );
std::string const err_erroneusnickname( std::string nickname );
std::string const err_nicknametoolong( std::string nickname );
std::string const err_nicknameinuse( std::string nickname );
std::string const err_unavailresource( std::string nickname_or_channel );
std::string const err_usernotinchannel( std::string nickname,
                                        std::string channel );
std::string const err_notonchannel( std::string channel );
std::string const err_useronchannel( std::string user,
                                     std::string channel );
std::string const err_nologin( std::string user );
std::string const err_summondisabled( void );
std::string const err_usersdisabled( void );
std::string const err_notregistered( void );
std::string const err_needmoreparams( std::string command );
std::string const err_alreadyregistred( void );
std::string const err_nopermforhost( void );
std::string const err_passwdmismatch( void );
std::string const err_yourebannedcreep( void );
std::string const err_youwillbebanned( void );
std::string const err_keyset( std::string channel );
std::string const err_channelisfull( std::string channel );
std::string const err_unknownmode( std::string channel, std::string modechar );
std::string const err_inviteonlychan( std::string channel );
std::string const err_bannedfromchan( std::string channel );
std::string const err_badchannelkey( std::string channel );
std::string const err_badchanmask( std::string channel );
std::string const err_nochanmodes( std::string channel );
std::string const err_banlistfull( std::string channel, std::string modechar );
std::string const err_noprivileges( void );
std::string const err_chanoprivsneeded( std::string channel );
std::string const err_cantkillserver( void );
std::string const err_restricted( void );
std::string const err_uniqopprivsneeded( void );
std::string const err_nooperhost( void );
std::string const err_umodeunknownflag( void );
std::string const err_usersdontmatch( void );
}
