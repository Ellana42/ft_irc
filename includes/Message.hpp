#ifndef MESSAGE_H
#define MESSAGE_H

#include "ft_irc.hpp"

#define MAX_SIZE 512
#define MIN_SIZE 2

class Message
{
	private:

	public:
		Message( std::string content );
		virtual ~Message();
};
#endif /* MESSAGE_H */
