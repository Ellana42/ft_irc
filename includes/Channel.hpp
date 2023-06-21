#ifndef CHANNEL_H
#define CHANNEL_H

#include "User.hpp"
#include "ft_irc.hpp"
#include "Password.hpp"
#include <set>

#define MAX_CHAN_NAME_LENGTH 50

class Channel
{
	private:
		typedef std::pair<std::string, User *> pair_nick_user;
		typedef std::pair<std::string, std::string> pair_nick_mode;

		std::string name;
		std::map<std::string, User *> users;

		std::string mode;
		std::string creator_nick;

		std::string topic;

		std::set<std::string> operators;

		bool topic_restricted;
		bool invite_only;
		bool has_password;
		bool has_user_limit;

		size_t user_limit;
		Password & password_handler;
		std::string channel_password;

		std::set<std::string> invited_users;

	public:
		Channel( std::string name, Password & password_handler );
		Channel( std::string name, User & creator, Password & password_handler );
		virtual ~Channel();

		void set_name( std::string name );
		std::string const & get_name( void ) const;
		void set_creator( std::string nick );
		void set_topic( std::string new_topic );
		std::string get_topic( void ) const;
		std::string const & get_creator( void ) const;
		std::string const & get_mode( void ) const;
		void set_modes( std::string modes_to_add, std::string modes_to_remove );
		void add_modes( std::string mode_string );
		void remove_modes( std::string mode_string );
		void add_invited_user( std::string nick );
		void remove_invited_user( std::string nick );
		void flush_invites( void );
		std::string get_modestring( void ) const;

		void set_topic_restricted( bool setting );
		bool is_topic_restricted() const;
		void set_invite_only( bool setting );
		bool is_invite_only() const;
		void remove_password();
		void set_password( std::string password );
		bool is_password_protected() const;
		bool check_password( std::string password ) const;
		void set_user_limit( int limit );
		void remove_user_limit( );
		bool has_user_limitation() const;
		bool is_at_limit() const;

		bool is_invited( User & user ) const;
		bool is_invited( std::string nickname ) const;

		bool has_mode( char c );
		bool is_operator( User & user );
		bool is_creator( User & user );
		void add_operator( User & user );
		void remove_operator( User & user );
		bool is_operator( std::string nick );
		bool is_creator( std::string nick );
		void add_operator( std::string nick );
		void remove_operator( std::string nick );

		void add_user( User & user );
		void remove_user( User & user );
		void update_user_nick( User & user, std::string new_nick );
		void send_reply( std::string reply );
		void send_reply( std::string reply, User & user_to_ignore );

		std::list<User *> get_user_list( void );
		unsigned int get_nbr_users( void );
		std::string get_user_list_string( void );
		bool is_user_in_channel( User & user );
		bool is_user_in_channel( std::string nickname );
		bool is_empty( void );

		class AlreadyInChannelException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class InvalidChannelNameException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif /* CHANNEL_H */
