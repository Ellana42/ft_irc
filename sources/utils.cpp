#include "ft_irc.hpp"

bool is_in( char c, std::string str )
{
	if ( str.find( c ) != std::string::npos )
	{
		return ( true );
	}
	return ( false );
}

bool is_channel( std::string name )
{
	const std::string channel_types = "#&";
	if ( name.size() <= 0 )
	{
		return ( false );
	}
	if ( is_in( name[0], channel_types ) )
	{
		return ( true );
	}
	return ( false );
}

std::string string_to_lowercase( std::string string )
{
	std::string lowercase = string;
	std::string::iterator it = lowercase.begin();
	for ( ; it != lowercase.end(); it++ )
	{
		*it = std::tolower( *it );
	}
	return ( lowercase );
}
