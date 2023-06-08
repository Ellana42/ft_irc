#include "Password.hpp"
#include "ft_irc.hpp"

Password::Password( std::string connection_password ) {
	if ( connection_password.empty() )
	{
		connection_password_hash = DEFAULT_CONNECTION_PASSWORD;
		return ;
	}
	connection_password_hash = create_sha256_hash( connection_password );
}

Password::~Password() {}

std::string Password::create_sha256_hash( std::string password )
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	unsigned const char * plain_text = reinterpret_cast<unsigned const char *>( password.c_str() );
	SHA256( plain_text, password.size(), hash );

	std::stringstream ss;
	for ( int i = 0; i < SHA256_DIGEST_LENGTH; i++ )
	{
		ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast<int>( hash[i] );
	}
	std::cout << "Created hash from [" << plain_text << "]: " << ss.str() << std::endl;
	return ( ss.str() );
}

void Password::save_password( std::string channel, std::string password )
{
	std::string hash = create_sha256_hash( password );
	
	std::map<std::string, std::string>::iterator it = passwords.find( channel );
	if ( it != passwords.end() )
	{
		it->second = hash;
	}
	else
	{
		passwords.insert(std::pair<std::string, std::string>( channel, hash ));
	}
}

bool Password::validate_connection_password( std::string password )
{
	return (validate_password(connection_password_hash, password ));
}

bool Password::validate_channel_password( std::string channel, std::string password )
{
	std::map<std::string, std::string>::iterator it = passwords.find( channel );
	if ( it == passwords.end() )
	{
		throw ( std::out_of_range( "Channel has no password" ));
	}
	return (validate_password( it->second, password ));
}

bool Password::validate_password( std::string hash, std::string password )
{
	std::string password_hash = create_sha256_hash( password );

	if ( password_hash == hash )
	{
		std::cout << "Passwords match !" << std::endl;
		return ( true );
	}
	else
	{
		std::cout << "Incorrect password..." << std::endl;
		return ( false );
	}
}
