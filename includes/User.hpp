#ifndef USER_H
#define USER_H

#include "Context.hpp"
#include <iostream>

class User
{
	private:
		std::string nickname;
		std::string username;
		std::string hostname;
		Context *context;
		int	socket;

	public:
		User();
		User( const User & src );
		User & operator=( const User & rhs );
		virtual ~User();
};

#endif /* USER_H */
