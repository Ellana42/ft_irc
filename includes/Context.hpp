#ifndef CONTEXT_H
#define CONTEXT_H

#include "ft_irc.hpp"

class User;
class Channel;

class Context
{
	private:

		std::map<std::string, User> users;
		std::map<std::string, Channel> channels;

	public:
		Context();
		Context( const Context & src );
		Context & operator=( const Context & rhs );
		virtual ~Context();

		void transmit_message( void );
};

#endif /* CONTEXT_H */
