#include "../includes/Application.hpp"
#include "../includes/ft_irc.hpp"

void examineChar( char c )
{
	if( c == '\n' )
	{
		std::cout << "\\n";
	}
	else if( c == '\r' )
	{
		std::cout << "\\r";
	}
	else if( c == '\b' )
	{
		std::cout << "\\b";
	}
	else if( c == '\t' )
	{
		std::cout << "\\t";
	}
	else if( c == '\a' )
	{
		std::cout << "\\a";
	}
	else if( c == '\v' )
	{
		std::cout << "\\v";
	}
	else if( c == '\0' )
	{
		std::cout << "\\0";
	}
	else
	{
		std::cout << c;
	}
}

void examineCharStar( char *cs )
{
	size_t i;
	for( i = 0; i < std::strlen( cs ); i++ )
	{
		examineChar( cs[i] );
	}
}

void examineString( std::string s )
{
	size_t i;
	if( s != "" )
		for( i = 0; i < s.length(); i++ )
		{
			examineChar( s[i] );
		}
}
