#ifndef MESSAGE_H
#define MESSAGE_H

#include "ft_irc.hpp"

// Maybe subclass for all of these ?
enum Command { HELP, JOIN, KICK, LIST, NAMES, NICK, PART, PRIVMSG, QUIT, USERS, WHO };

class Message
{
	private:

		Command command;

		std::string content;
		std::string nickname;
		std::string message;
		std::string msgtarget;

		std::list<std::string> channels;
		std::list<std::string> clients;
		std::list<std::string> names;

	public:
		Message();
		Message( const Message & src );
		Message & operator=( const Message & rhs );
		virtual ~Message();
};

#endif /* MESSAGE_H */
