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

const std::string Mode_Handler::accepted_modes = "ioO";

Mode_Handler::Mode_Handler( Context & context, User & sender,
                            Message & message ) : context( context ), sender( sender ), message( message )
{
	target = message.get( "target" );

	handlers["iu"] = &Mode_Handler::handle_i_user;
	handlers["ic"] = &Mode_Handler::handle_i_channel;
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
	if ( is_in( 'o', added_modes ) || is_in( 'o', removed_modes )
	        || is_in( 'O', added_modes ) || is_in( 'o', removed_modes ) )
	{
		std::cout << "There is o" << std::endl;
	}
	if ( is_in( 'i', added_modes ) || is_in( 'i', removed_modes )
	        || is_in( 'O', added_modes ) || is_in( 'o', removed_modes ) )
	{
		std::cout << "There is i" << std::endl;
	}
	else
	{
		std::cout << "There is no o" << std::endl;
	}
}

void Mode_Handler::handle_i_user()
{
	return;
}

void Mode_Handler::handle_i_channel()
{
	return;
}

void Mode_Handler::handle_o_user()
{
	return;
}

void Mode_Handler::handle_o_channel()
{
	return;
}
