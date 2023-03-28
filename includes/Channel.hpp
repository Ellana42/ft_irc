#ifndef CHANNEL_H
#define CHANNEL_H

#include "User.hpp"
#include "ft_irc.hpp"

class Channel
{
	private:
		typedef std::pair<std::string, User *> pair_string_user;

		std::string name;
		std::map<std::string, User *> users;

	public:
		Channel( std::string name );
		Channel( std::string name, User & creator );
		virtual ~Channel();

		void set_name( std::string name );
		std::string const & get_name( void ) const;

		void add_user( User & user );
		void remove_user( User & user );
		void send_reply( std::string reply );

		std::string get_user_list( void );
		bool is_user_in_channel( User & user );
		bool is_empty( void );
};

#endif /* CHANNEL_H */
