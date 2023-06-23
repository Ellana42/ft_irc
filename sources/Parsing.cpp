#include "../includes/Parsing.hpp"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <string>
#include "Tokenizer.hpp"

#define NUMBER_CMD 24

std::string commands[NUMBER_CMD] = {"ADMIN", "INFO", "VERSION", "USERS", "NICK", "PRIVMSG", "USER", "QUIT", "JOIN", "LIST", "NAMES", "SUMMON", "KICK", "PART", "MODE", "CAP", "PASS", "KICK", "INVITE", "TOPIC", "PING", "PONG"};
std::string params[NUMBER_CMD][10] = {{"target"}, {"target"}, {}, {}, {"nickname"}, {"msgtarget", "text to be sent"}, {"user", "mode", "unused", "realname"}, {"Quit Message"}, {"channel", "key"}, {"channel"}, {"channel", "target"}, {"user", "target", "channel"}, {"channel", "user", "comment"}, {"channel", "Part Message"}, {"target", "modestring", "mode arguments"}, {"a"}, {"password"}, {"channel", "user", "comment"}, {"nickname", "channel"}, {"channel", "topic"}, {"token"}, {"token"}};

mode params_states[NUMBER_CMD][10] = {{Optional}, {Optional}, {}, {}, {Mandatory}, {Mandatory, Optional}, {Mandatory, Mandatory, Mandatory, Mandatory}, {Optional}, {List, ListOptional}, {ListOptional}, {ListOptional, Optional}, {Mandatory, Optional, Optional}, {List, List, Optional}, {List, Optional}, {Mandatory, Optional, MultiOptional}, {Optional}, {Optional}, {Mandatory, List, Optional}, {Mandatory, Mandatory}, {Mandatory, Optional}, {Mandatory}, {Mandatory}};


Parsing::Parsing( std::string raw_content ) : tokenizer( Tokenizer(
	            raw_content ) ), current( 0 )
{
	tokenizer.tokenize();
	tokens = tokenizer.get_tokens();
	if ( tokens.size() == 0 )
	{
		throw Parsing::UnknownCommandException();
	}
	command = tokens[0]; // TODO: add to upper here
	command_to_upper( command );
	move();
}

void Parsing::command_to_upper( std::string & command )
{
	std::string::iterator it = command.begin();
	for ( ; it != command.end(); it++ )
	{
		*it = toupper( *it );
	}
}

void Parsing::parse( void )
{
	if ( !is_in_array( command, commands, NUMBER_CMD ) )
	{
		throw Parsing::UnknownCommandException();
	}

	if ( is_in_array( command, commands, NUMBER_CMD ) )
	{
		try
		{
			parse_complex();
		}
		catch ( std::out_of_range const &e )
		{
			throw NeedMoreParamsException();
		}
	}
}

void Parsing::parse_no_arg( void )
{
	if ( tokens.size() > 1 )
	{
		throw Parsing::TooManyParamsException();
	}
	return;
}

void Parsing::parse_complex( void )
{
	unsigned int command_index = get_array_index( command, commands, NUMBER_CMD );
	unsigned int i = 0;
	std::string current_param = params[command_index][i] ;
	mode current_type = params_states[command_index][i] ;

	while ( !current_param.empty() )
	{
		if ( !set_current_arg( current_param, current_type ) )
		{
			throw NeedMoreParamsException();
		}
		move();
		i++;
		current_param = params[command_index][i] ;
		current_type = params_states[command_index][i] ;
	}
	if ( tokens.size() > i + 1 && command != "MODE" )
	{
		throw TooManyParamsException();
	}
}

std::string Parsing::get_current_token()
{
	if ( current >= tokens.size() )
	{
		throw std::out_of_range( "No more tokens" );
	}
	return ( tokens[current] );
}

bool Parsing::set_current_arg( std::string arg_name )
{
	try
	{
		std::string current_token = get_current_token();
		args[arg_name] = current_token;
		return ( true );
	}
	catch ( std::out_of_range const &e )
	{
		return ( false );
	}
}

std::list<std::string> Parsing::arg_to_list( std::string current_token )
{
	std::list<std::string> args_list;

	char *token = ( char * )current_token.c_str();

	char * subtoken = std::strtok( token, "," );
	args_list.push_back( ( std::string )subtoken );
	while ( subtoken != NULL )
	{
		subtoken = strtok( NULL, "," );
		if ( subtoken != NULL )
		{
			args_list.push_back( subtoken );
		}
	}
	return args_list;
}

bool Parsing::set_current_arg( std::string arg_name, mode arg_type )
{
	try
	{
		std::string current_token = get_current_token();
		if ( arg_type == List || arg_type == ListOptional )
		{
			args_lists[arg_name] = arg_to_list( current_token );
		}
		else if ( arg_type == MultiOptional )
		{
			args_lists[arg_name] = get_rest_tokens( current_token );
		}
		else
		{
			args[arg_name] = current_token;
		}
	}
	catch ( std::out_of_range const &e )
	{
		if ( arg_type == Mandatory || arg_type == List )
		{
			return ( false );
		}
		return ( true );
	}
	return ( true );
}

std::list<std::string> Parsing::get_rest_tokens( std::string current_token )
{
	std::list<std::string> arguments;
	std::string token;
	bool unfinished = true;

	arguments.push_back( current_token );
	while ( unfinished )
	{
		try
		{
			move();
			token = get_current_token();
			arguments.push_back( token );
		}
		catch( std::out_of_range & e )
		{
			( void )e;
			unfinished = false;
		}
	}
	return arguments;
}

bool Parsing::set_current_arg_list( std::string arg_name )
{
	char *subtoken;

	try
	{
		std::string current_token = get_current_token();
		char *token = ( char * )current_token.c_str();

		subtoken = std::strtok( token, "," );
		args[arg_name] = subtoken;
		while ( subtoken != NULL )
		{
			subtoken = strtok( NULL, "," );
			args[arg_name] = subtoken;
		}
		return ( true );
	}
	catch ( std::out_of_range const &e )
	{
		return ( false );
	}
}

void Parsing::move( void )
{
	current++;
}

std::string Parsing::get_command( void )
{
	return ( command );
}

std::string Parsing::get( std::string arg_name )
{
	return ( args[arg_name] );
}

std::list<std::string> Parsing::get_list( std::string arg_name )
{
	return ( args_lists[arg_name] );
}

std::vector<std::string> Parsing::get_tokens( void )
{
	return ( tokens );
}

bool Parsing::has_arg( std::string arg_name )
{
	// XXX might be improved by checking the command type and which arguments should exist
	if ( args.count( arg_name ) == 0 )
	{
		return ( false );
	}
	return ( true );
}

bool Parsing::has_list( std::string arg_name )
{
	// XXX might be improved by checking the command type and which arguments should exist
	if ( args_lists.count( arg_name ) == 0 )
	{
		return ( false );
	}
	return ( true );
}


Parsing::~Parsing() {}

const char* Parsing::NeedMoreParamsException::what() const throw()
{
	return ( "Not enough parameters provided" );
}

const char* Parsing::TooManyParamsException::what() const throw()
{
	return ( "Too many parameters provided" );
}

const char* Parsing::UnknownCommandException::what() const throw()
{
	return ( "Unknown command" );
}
