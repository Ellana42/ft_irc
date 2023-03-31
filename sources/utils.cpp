#include "ft_irc.hpp"

bool is_in( char c, std::string str )
{
	if ( str.find( c ) != std::string::npos )
	{
		return ( true );
	}
	return ( false );
}

template <typename T, typename U>
void delete_map( std::map<T, U> & map )
{
	typename std::map<T, U>::iterator it = map.begin();
	for ( ; it != map.end(); it++ )
	{
		delete ( it->second );
	}
	map.clear();
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

template <typename T>
bool is_in_list( std::list<T> list, T elem )
{
	typename std::list<T>::iterator it = list.begin();
	for ( ; it != list.end(); it++ )
	{
		if ( *it == elem )
		{
			return ( true );
		}
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
