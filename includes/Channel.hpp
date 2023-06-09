#ifndef CHANNEL_H
#define CHANNEL_H

#include "User.hpp"
#include "ft_irc.hpp"
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

		std::set<std::string> operators;

		bool topic_restricted;
		bool invite_only;
		bool has_password;
		bool has_user_limit;

		int user_limit;

	public:
		Channel( std::string name );
		Channel( std::string name, User & creator );
		virtual ~Channel();

		void set_name( std::string name );
		std::string const & get_name( void ) const;
		void set_creator( std::string nick );
		std::string const & get_creator( void ) const;
		std::string const & get_mode( void ) const;
		void set_modes( std::string modes_to_add, std::string modes_to_remove );
		void add_modes( std::string mode_string );
		void remove_modes( std::string mode_string );

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

		std::list<User *> get_user_list( void );
		unsigned int get_nbr_users( void );
		std::string get_user_list_string( void );
		bool is_user_in_channel( User & user );
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
