#include "Message_Handler.hpp"
#include "Mode_Handler.hpp"
#include "Message.hpp"
#include "Context.hpp"
#include "Channel.hpp"
#include "Mode_Parsing.hpp"
#include "Parsing.hpp"
#include <cctype>
#include <exception>
#include <list>
#include <stdexcept>
#include <string>

// TODO: Maybe implement mode arguments

const std::string Mode_Handler::accepted_modes = "ioO";

Mode_Handler::Mode_Handler( Context & context, User & sender,
                            Message & message ) : context( context ), sender( sender ), message( message )
{
	target = message.get( "target" );

	handlers['i'][User_]["+"] = &Mode_Handler::handle_i_user_add;
	handlers['i'][User_]["-"] = &Mode_Handler::handle_i_user_rm;
	/* handlers['o'][User_]["+"] = &Mode_Handler::handle_o_user_add; */
	/* handlers['o'][User_]["-"] = &Mode_Handler::handle_o_user_rm; */

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

	set_type();
	set_modestring();
	apply_modes();
}

Mode_Handler::~Mode_Handler() {}

void Mode_Handler::set_type()
{

	if ( is_channel( target ) )
	{
		if ( !context.does_channel_exist( target ) )
		{
			sender.send_reply( rpl::err_nosuchchannel( sender, target ) );
			return;
		}
		target_channel = &context.get_channel_by_name( target );
	}
	else
	{
		if ( !context.does_user_with_nick_exist( target ) )
		{
			sender.send_reply( rpl::err_nosuchnick( sender, target ) );
			return;
		}
		type_target = User_;
		target_user = &context.get_user_by_nick( target );
		if ( target != sender.get_nickname() )
		{
			sender.send_reply( rpl::err_usersdontmatch( sender ) );
			return;
		}
	}
}

bool Mode_Handler::has_unknown_modes( std::string modes )
{
	for ( unsigned int i = 0; i < modes.size(); i++ )
	{
		if ( !is_in( modes[i], accepted_modes ) )
		{
			return ( true );
		}
	}
	return ( false );
}


void Mode_Handler::set_modestring()
{
	if ( !message.has( "modestring" ) )
	{
		// TODO: implment rpl umodeis
		return;
	}
	ModeParsing parsing( message.get( "modestring" ) );
	try
	{
		parsing.parse();
		added_modes = parsing.get_added_modes();
		removed_modes = parsing.get_removed_modes();
		if ( has_unknown_modes( added_modes ) || has_unknown_modes( removed_modes ) )
		{
			sender.send_reply( rpl::err_umodeunknownflag( sender ) );
		}
	}
	catch ( ModeParsing::InvalidModestringException & e )
	{
		sender.send_reply( rpl::err_invalidmodestring() );
	}
}

void Mode_Handler::apply_modes()
{
	std::string::iterator it = added_modes.begin();
	for ( ; it != added_modes.end(); it++ )
	{
		( ( this )->*( handlers[ *it ][type_target]["+"] ) )();
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
	return;
}

void Mode_Handler::handle_i_channel_rm()
{
	return;
}

void Mode_Handler::handle_t_channel_add()
{
	return;
}

void Mode_Handler::handle_t_channel_rm()
{
	return;
}

void Mode_Handler::handle_k_channel_add()
{
	return;
}

void Mode_Handler::handle_k_channel_rm()
{
	return;
}

void Mode_Handler::handle_o_channel_add()
{
	return;
}

void Mode_Handler::handle_o_channel_rm()
{
	return;
}

void Mode_Handler::handle_l_channel_add()
{
	return;
}

void Mode_Handler::handle_l_channel_rm()
{
	return;
}

// OLD IMPLEM for o and O modes
/* if ( is_in( 'o', added_modes ) || is_in( 'o', removed_modes ) */
/*         || is_in( 'O', added_modes ) || is_in( 'o', removed_modes ) ) */
/* { */
/* 	if ( type_target == User_ ) */
/* 	{ */
/* 		target_user->remove_modes( */
/* 		    removed_modes ); */
/* 	} */
/* 	else */
/* 	{ */
/* 		if ( target_channel->is_operator( sender ) ) */
/* 		{ */
/* 			if ( message.has( "mode arguments" ) ) */
/* 			{ */
/* 				try */
/* 				{ */
/* 					User target_user = context.get_user_by_nick( */
/* 					                       message.get( "mode arguments" ) ); */

/* 					if ( is_in( 'o', added_modes ) ) */
/* 					{ */
/* 						target_channel->set_modes( target_user, "o" ); */
/* 					} */
/* 					target_channel->remove_modes( target_user, removed_modes ); */
/* 				} */
/* 				catch ( std::out_of_range & e ) */
/* 				{ */
/* 					if ( message.has( "mode arguments" ) ) */
/* 					{ */
/* 						sender.send_reply( rpl::err_nosuchnick( sender, */
/* 						                                        message.get( "mode arguments" ) ) ); */
/* 					} */
/* 					else */
/* 					{ */
/* 						sender.send_reply( rpl::err_nosuchnick( sender, "" ) ); */
/* 					} */
/* 				} */
/* 			} */
/* 			else */
/* 			{ */
/* 				if ( message.has( "mode arguments" ) ) */
/* 				{ */
/* 					sender.send_reply( rpl::err_nosuchnick( sender, */
/* 					                                        message.get( "mode arguments" ) ) ); */
/* 				} */
/* 				else */
/* 				{ */
/* 					sender.send_reply( rpl::err_nosuchnick( sender, */
/* 					                                        "" ) ); */
/* 				} */
/* 			} */
/* 		} */
/* 		else */
/* 		{ */
/* 			sender.send_reply( rpl::err_chanoprivsneeded( sender, */
/* 			                   target_channel->get_name() ) ); */
/* 		} */
/* 	} */
/* } */
