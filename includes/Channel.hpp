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
		Channel( std::string name, User & creator );
		virtual ~Channel();

		void set_name( std::string name );
		std::string const & get_name( void ) const;

		void add_user_to_channel( User & user );
		void remove_user_from_channel( User & user );
		void send_reply( std::string reply );

		bool is_user_in_channel( User & user );
};

#endif /* CHANNEL_H */
