#include "Mode_Parsing.hpp"
#include <cctype>
#include <exception>

ModeParsing::ModeParsing( std::string modestring ) : modestring( modestring ),
	current_state( ModeChar ), current_type( Plus ), position( 0 ) {}

ModeParsing::~ModeParsing() {}

void ModeParsing::parse( void )
{
	while ( position < modestring.size() )
	{
		switch ( current_state )
		{
			case PlusMinus:
				parse_plus_minus();
				break;
			case ModeChar:
				parse_mode_char();
				break;
		}
	}
}

void ModeParsing::parse_plus_minus( void )
{
	if ( get_char() == '+' )
	{
		current_type = Plus;
		current_state = ModeChar;
		move();
	}
	else if ( get_char() == '-' )
	{
		current_type = Minus;
		current_state = ModeChar;
		move();
	}
	else
	{
		throw InvalidModestringException();
	}

}

void ModeParsing::parse_mode_char( void )
{
	if ( std::isalpha( get_char() ) )
	{
		if ( current_type == Plus )
		{
			added_modes.push_back( get_char() );
			move();
		}
		else if ( current_type == Minus )
		{
			removed_modes.push_back( get_char() );
			move();
		}
	}
	else if ( get_char() == '-' || get_char() == '+' )
	{
		current_state = PlusMinus;
	}
	else
	{
		throw InvalidModestringException();
	}
}

void ModeParsing::move( void )
{
	position++;
}

char ModeParsing::get_char( void )
{
	if ( position < modestring.size() )
	{
		return ( modestring[position] );
	}
	else
	{
		throw std::out_of_range( "Requested position is beyond modestring" );
	}
}


std::string ModeParsing::get_added_modes( void )
{
	return ( added_modes );
}

std::string ModeParsing::get_removed_modes( void )
{
	return ( removed_modes );
}
