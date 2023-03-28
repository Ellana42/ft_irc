#ifndef USER_H
#define USER_H

#include "ft_irc.hpp"

#define MAX_USER_SIZE 19

class Context;

class User
{
	private:
		std::string nickname;
		std::string username;
		std::string hostname;
		std::string realname;
		std::string identifier;

		bool fully_registered;
		Context & context;
		int	socket;

		/* User(); */
		void update_identifier( void );
		bool username_is_valid( std::string username );

	public:
		User( Context & context, int socket );
		virtual ~User();

		std::string const & get_nickname( void ) const;
		std::string const & get_username( void ) const;
		std::string const & get_realname( void ) const;
		std::string const & get_hostname( void ) const;
		std::string const & get_identifier( void ) const;
		int const & get_socket( void ) const;
		bool is_fully_registered( void ) const;

		void set_nickname( std::string nickname );
		void set_username( std::string username );
		void set_realname( std::string realname );
		void set_hostname( std::string hostname );
		void set_registered( void );

		void read_from_socket( void );
		void send_reply( std::string reply );
		bool has_nickname( void );
		bool has_user_info( void );


		class InvalidUsernameException : public std::exception
		{
				/* public: */
				/* 	virtual const char* what() const throw(); */
		};

		class InvalidNicknameException : public std::exception
		{
				/* public: */
				/* 	virtual const char* what() const throw(); */
		};
};

std::ostream & operator<<( std::ostream & os, User const & obj );

#endif /* USER_H */
