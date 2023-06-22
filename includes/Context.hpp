#ifndef CONTEXT_H
#define CONTEXT_H

#include "Password.hpp"
#include "ft_irc.hpp"
#include "Message.hpp"
#include "Message_Handler.hpp"
#include "reply.hpp"
#include "Application.hpp"

# define DEFAULT_CHAN "*"

class Application;
class User;
class Channel;

class Context
{
	private:
		typedef std::pair<std::string, User *> pair_string_user;
		typedef std::pair<int, User *> pair_int_user;
		typedef std::pair<std::string, Channel *> pair_string_chan;

		std::map<int, User *> unregistered_users;
		std::map<std::string, User *> registered_users;
		std::map<std::string, Channel *> channels;

		Application & application;
		Password & password_handler;
		Message_Handler * message_handler;

		Context( const Context & src );
		Context & operator=( const Context & rhs );

		void remove_registered_user( User & user );
		void remove_unregistered_user( User & user );
		void create_channel( std::string name );

	public:
		Context( Application & application, Password & password_handler );
		virtual ~Context();

		void create_unregistered_user( int socket );
		void register_user( User & user );
		void remove_user( User & user );
		void remove_user( int socket );
		void create_channel( User & user, std::string name );
		void remove_channel( Channel & channel );
		void update_user_nick( User & user, std::string new_nick );

		void handle_message( User & sender, std::string raw_message );

		User & get_user_by_socket( int socket );
		User & get_user_by_nick( std::string nickname );
		bool does_user_with_nick_exist( std::string nickname );

		Channel & get_channel_by_name( std::string name );
		Channel & get_default_channel( void );
		std::list<std::string> get_channel_names( void );
		void add_user_to_channel( User & user, std::string channel_name );
		void remove_user_from_channel( User & user, std::string channel_name );
		void remove_user_from_all_channels( User & user );

		bool does_channel_exist( std::string name );

		bool is_user_in_any_channel( User & user );
		std::list<Channel *> get_user_channels( User & user );
		std::list<User *> get_users_in_same_channels( User & user );

		void check_connection_password( std::string password );
		void send_message( int socket, std::string message );
		void force_disconnect_user( User & user );

		void debug_print_unregistered_users( void ) const;
		void debug_print_registered_users( void ) const;
		void debug_print_channels( void ) const;

		class CouldNotFindUserException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif /* CONTEXT_H */
