#include "Message_Handler.hpp"
#include "Mode_Handler.hpp"
#include "Message.hpp"
#include "Context.hpp"
#include "Channel.hpp"
#include "Mode_Parsing.hpp"
#include "Parsing.hpp"
#include "reply.hpp"
#include <cctype>
#include <cstdlib>
#include <exception>
#include <list>
#include <stdexcept>
#include <string>

Mode_Handler::Mode_Handler( Context & context, User & sender,
                            Message & message ) : context( context ), sender( sender ), message( message )
{
	target = message.get( "target" );


	handlers['i'][User_]["+"] = &Mode_Handler::handle_i_user_add;
	handlers['i'][User_]["-"] = &Mode_Handler::handle_i_user_rm;

	handlers['i'][Channel_]["+"] = &Mode_Handler::handle_i_channel_add;
	handlers['i'][Channel_]["-"] = &Mode_Handler::handle_i_channel_rm;
	handlers['t'][Channel_]["+"] = &Mode_Handler::handle_t_channel_add;
	handlers['t'][Channel_]["-"] = &Mode_Handler::handle_t_channel_rm;
	handlers['k'][Channel_]["+"] = &Mode_Handler::handle_k_channel_add;
	handlers['k'][Channel_]["-"] = &Mode_Handler::handle_k_channel_rm;
	handlers['o'][Channel_]["+"] = &Mode_Handler::handle_o_channel_add;
	handlers['o'][Channel_]["-"] = &Mode_Handler::handle_o_channel_rm;
	handlers['l'][Channel_]["+"] = &Mode_Handler::handle_l_channel_add;
	handlers['l'][Channel_]["-"] = &Mode_Handler::handle_l_channel_rm;

	if ( set_type() )
	{
		return ;
	}
	if ( set_modestring() )
	{
		return;
	}
	set_arguments();
	if ( !target_channel->is_user_in_channel( sender ) )
	{
		sender.send_reply( rpl::err_notonchannel( sender,
		                   target ) );
		return;
	}
	if ( ! target_channel->is_operator( sender ) )
	{
		sender.send_reply( rpl::err_chanoprivsneeded( sender,
		                   target ) );
		return;
	}
	apply_modes();
}

Mode_Handler::~Mode_Handler() {}

std::string Mode_Handler::get_current_argument()
{
	std::string current_argument;
	if ( arguments.size() == 0 )
	{
		throw std::out_of_range( "No more arguments" );
	}
	current_argument = arguments.front();
	arguments.pop_front();
	return current_argument;
}

bool Mode_Handler::set_type()
{

	if ( is_channel( target ) )
	{
		type_target = Channel_;
		if ( !context.does_channel_exist( target ) )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, target ) );
			return 1;
		}
		target_channel = &context.get_channel_by_name( target );
	}
	else if ( context.does_user_with_nick_exist( target ) )
	{
		return 1;
	}
	else
	{
		sender.send_reply( rpl::err_nosuchchannel( sender, target ) );
		return 1;
	}
	return 0;
}

bool Mode_Handler::has_unknown_modes( std::string modes )
{
	for ( unsigned int i = 0; i < modes.size(); i++ )
	{
		if ( !handlers.count( modes[i] ) )
		{
			return ( true );
		}
	}
	return ( false );
}

bool Mode_Handler::has_unknown_modes( char mode )
{
	if ( !handlers.count( mode ) )
	{
		return ( true );
	}
	return ( false );
}

std::string Mode_Handler::filter_modes( std::string modestring )
{
	std::string cleaned;

	for ( std::string::iterator it = modestring.begin();
	        it != modestring.end();
	        it++ )
	{
		if ( has_unknown_modes( *it ) )
		{
			sender.send_reply( rpl::err_unknownmode( sender, target, *it ) );
		}
		else
		{
			cleaned += *it;
		}
	}
	return ( cleaned );
}

bool Mode_Handler::set_modestring()
{
	std::string cleaned_added_modes;
	std::string cleaned_removed_modes;

	if ( !message.has( "modestring" ) )
	{
		if ( type_target == User_ )
		{
			sender.send_reply( rpl::umodeis( message, *target_user ) );
			return 1;
		}
		sender.send_reply( rpl::channelmodeis( message, *target_channel ) );
		return 1;
	}
	ModeParsing parsing( message.get( "modestring" ) );
	try
	{
		parsing.parse();
		added_modes = filter_modes( parsing.get_added_modes() );
		removed_modes = filter_modes( parsing.get_removed_modes() );
	}
	catch ( ModeParsing::InvalidModestringException & e )
	{
		sender.send_reply( rpl::err_invalidmodestring() );
		return 1;
	}
	return 0;
}

void Mode_Handler::set_arguments()
{
	if ( message.has_list( "mode arguments" ) )
	{
		arguments = message.get_list( "mode arguments" );
		return;
	}
}

void Mode_Handler::apply_modes()
{
	std::string::iterator it = added_modes.begin();
	for ( ; it != added_modes.end(); it++ )
	{
		( ( this )->*( handlers[ *it ][type_target]["+"] ) )();
	}
	std::string::iterator itr = removed_modes.begin();
	for ( ; itr != removed_modes.end(); itr++ )
	{
		( ( this )->*( handlers[ *itr ][type_target]["-"] ) )();
	}
}

void Mode_Handler::handle_i_user_add()
{
	// Compatibility with irssi
	return;
}

void Mode_Handler::handle_i_user_rm()
{
	// Compatibility with irssi
	return;
}

void Mode_Handler::handle_i_channel_add()
{
	if ( !target_channel->is_invite_only() )
	{
		target_channel->set_invite_only( true );
		target_channel->flush_invites();
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "+i" ) );
	}
	return;
}

void Mode_Handler::handle_i_channel_rm()
{
	if ( target_channel->is_invite_only() )
	{
		target_channel->set_invite_only( false );
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "-i" ) );
	}
	return;
}

void Mode_Handler::handle_t_channel_add()
{
	if ( !target_channel->is_topic_restricted() )
	{
		target_channel->set_topic_restricted( true );
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "+t" ) );
	}
	return;
}

void Mode_Handler::handle_t_channel_rm()
{
	if ( target_channel->is_topic_restricted() )
	{
		target_channel->set_topic_restricted( false );
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "-t" ) );
	}
	return;
}

void Mode_Handler::handle_k_channel_add()
{
	std::string argument;

	try
	{
		argument = get_current_argument();
		if ( argument.find( ' ' ) != std::string::npos )
		{
			throw std::out_of_range( "Bad key" );
		}
	}
	catch ( std::out_of_range & e )
	{
		sender.send_reply( rpl::invalidmodeparam( sender, target_channel->get_name(),
		                   'k',
		                   "Invalid channel key" ) ) ;
		return;
	}
	target_channel->set_password( argument );
	target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
	                            "+k " + argument ) );
	return;
}

void Mode_Handler::handle_k_channel_rm()
{
	if ( target_channel->is_password_protected() )
	{
		target_channel->remove_password();
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "-k" ) );
	}
	return;
}

void Mode_Handler::handle_o_channel_add()
{
	std::string argument;
	try
	{
		argument = get_current_argument();
		User & new_operator = context.get_user_by_nick(
		                          argument ); // TODO: maybe specific response if exists
		if ( !target_channel->is_user_in_channel( new_operator ) )
		{
			sender.send_reply( rpl::err_usernotinchannel( sender,
			                   new_operator.get_nickname(), target_channel->get_name() ) );
			return;
		}
		if ( target_channel->is_operator( new_operator ) )
		{
			return;
		}
		target_channel->add_operator( new_operator );
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "+o " + argument ) );
		/* new_operator.send_reply( rpl::mode_channel( sender, *target_channel, */
		/* "+o " + argument ) ); */
	}
	catch ( std::out_of_range & e )
	{
		return;
	}
	catch ( Context::CouldNotFindUserException & e )
	{
		return;
	}
}

void Mode_Handler::handle_o_channel_rm()
{
	std::string argument;
	try
	{
		argument = get_current_argument();
		User & new_operator = context.get_user_by_nick( argument );
		if ( !target_channel->is_operator( new_operator ) )
		{
			return;
		}
		target_channel->remove_operator( new_operator );
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "-o " + argument ) );
		/* new_operator.send_reply( rpl::mode_channel( sender, *target_channel, */
		/*                          "-o " + argument ) ); */
	}
	catch ( std::out_of_range & e )
	{
		return;
	}
	catch ( Context::CouldNotFindUserException & e )
	{
		return;
	}
	return;
}

bool isInt( const std::string& str )
{
	int n;
	std::istringstream istreamObject( str );
	istreamObject >> std::noskipws >> n;
	return istreamObject.eof() && !istreamObject.fail();
}

void Mode_Handler::handle_l_channel_add()
{
	std::string argument;
	int limit;
	try
	{
		argument = get_current_argument();
		if ( isInt( argument ) )
		{
			limit =  std::atoi( argument.c_str() );
			if ( limit < 0 )
			{
				return;
			}
			target_channel->set_user_limit( limit );
			target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
			                            "+l " + argument ) );
		}
	}
	catch ( std::out_of_range & e )
	{
		return;
	}
	return;
}

void Mode_Handler::handle_l_channel_rm()
{
	if ( target_channel->has_user_limitation() )
	{
		target_channel->remove_user_limit();
		target_channel->send_reply( rpl::mode_channel( sender, *target_channel,
		                            "-l" ) );
	}
	return;
}
