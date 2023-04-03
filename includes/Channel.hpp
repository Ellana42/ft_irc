#ifndef CHANNEL_H
#define CHANNEL_H

#include "User.hpp"
#include "ft_irc.hpp"

#define MAX_CHAN_NAME_LENGTH 50

class Channel
{
	private:
		typedef std::pair<User *, std::string> pair_user_string;

		std::string name;
		std::map<User *, std::string> users;
		std::string mode;

	public:
		Channel( std::string name );
		Channel( std::string name, User & creator );
		virtual ~Channel();

		void set_name( std::string name );
		std::string const & get_name( void ) const;
		std::string const & get_mode( void ) const;
		void set_modes( std::string modes_to_add, std::string modes_to_remove );
		void add_modes( std::string mode_string );
		void remove_modes( std::string mode_string );
		void set_modes( User & user, std::string mode_string );
		void remove_modes( User & user, std::string mode_string );
		bool has_mode( char c );
		bool has_mode( User & user, char c );

		void add_user( User & user );
		void remove_user( User & user );
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
