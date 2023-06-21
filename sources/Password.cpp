#include "Password.hpp"
#include "ft_irc.hpp"
#include "log_event.hpp"

Password::Password( std::string connection_password ) {
	if ( connection_password.empty() )
	{
		log_event::info( "Password: No password provided, using default password" );
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
	log_event::info( "Password: Created hash", ss.str() );
	return ( ss.str() );
}

std::string Password::get_hash( std::string plain_text )
{
	return ( create_sha256_hash( plain_text ) );
}

void Password::validate_connection_password( std::string password )
{
	validate_password( connection_password_hash, password );
}

void Password::validate_password( std::string hash, std::string plain_text )
{
	std::string password_hash = create_sha256_hash( plain_text );

	if ( password_hash != hash )
	{
		log_event::info( "Password: Incorrect password..." );
		throw InvalidPasswordException();
	}
	log_event::info( "Password: Passwords match!" );
}

const char* Password::InvalidPasswordException::what() const throw()
{
	return ( "invalid password" );
}
