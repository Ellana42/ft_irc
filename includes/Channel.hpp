#ifndef CHANNEL_H
#define CHANNEL_H

#include "User.hpp"
#include "ft_irc.hpp"

class Channel
{
	private:
		std::string name;
		std::map<std::string, User *> users;

	public:
		Channel( User * creator );
		virtual ~Channel();
};

#endif /* CHANNEL_H */
