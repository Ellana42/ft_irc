#ifndef PASSWORD_H
#define PASSWORD_H

#include "ft_irc.hpp"

/* The default connection password is 'password', the sha256 hash is: */
#define DEFAULT_CONNECTION_PASSWORD "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"

class Password
{
	private:
		std::string connection_password_hash;

		std::string create_sha256_hash( std::string plain_text );

	public:
		Password( std::string connection_password );
		virtual ~Password();

		std::string get_hash( std::string plain_text );
		void validate_connection_password( std::string password );
		void validate_password( std::string hash, std::string password );

		class InvalidPasswordException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif /* PASSWORD_H */
