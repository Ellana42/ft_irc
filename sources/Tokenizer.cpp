#include "../includes/Tokenizer.hpp"

Tokenizer::Tokenizer( std::string raw_content ) : content( raw_content ),
	state( Param ), current_position( 0 ) {}

void Tokenizer::tokenize( void )
{
	while ( current_position <= content.size() )
	{
		if ( state == Param )
		{
			tokenize_param();
		}
		else if ( state == Space )
		{
			tokenize_space();
		}
		else if ( state == LongParam )
		{
			tokenize_long_param();
		}
	}
}

void Tokenizer::tokenize_param( void )
{
	switch ( current_char() )
	{
		case ' ':
			change_state( Space );
			if ( !buffer.empty() )
			{
				push_token();
			}
			move();
			break;
		case '\0':
			if ( !buffer.empty() )
			{
				push_token();
			}
			move();
			break;
		default:
			accumulate();
	}
}

void Tokenizer::tokenize_space( void )
{
	switch ( current_char() )
	{
		case ' ':
			move();
			break;
		case '\0':
			move();
			break;
		case ':':
			change_state( LongParam );
			move();
			break;
		default:
			change_state( Param );
	}
}

void Tokenizer::tokenize_long_param( void )
{
	switch ( current_char() )
	{
		case '\0':
			push_token();
			move();
			break;
		default:
			accumulate();
	}
}

char Tokenizer::current_char( void ) const
{
	if ( current_position < content.size() )
	{
		return ( content[current_position] );
	}
	return ( '\0' );
}

void Tokenizer::accumulate( void )
{
	buffer.push_back( current_char() );
	move();
}

void Tokenizer::move( void )
{
	current_position++;
}

void Tokenizer::change_state( State new_state )
{
	state = new_state;
}

void Tokenizer::push_token( void )
{
	tokens.push_back( buffer );
	buffer.clear();
}

std::vector<std::string> Tokenizer::get_tokens( void )
{
	return ( tokens );
}

Tokenizer::~Tokenizer() {}
