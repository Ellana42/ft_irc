#ifndef FT_IRC_H
#define FT_IRC_H

#include <list>
#include <map>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <map>
#include <utility>
#include <cstring>
#include <exception>
#include <new>
#include <stdexcept>
#include "Colors.h"

# define SERVER_PREFIX ":ircserv.42.fr"
# define SERVER_NAME "ircserv"
# define SERVER_CREATION "7/03/2023"
# define SERVER_VERSION "0.01"

# define ADMIN_INFO_1 "Paris, France"
# define ADMIN_INFO_2 "The best 42 Paris IRC server !"
# define ADMIN_EMAIL "iazimzha@student.42.fr mcombeau@student.42.fr mkaploun@student.42.fr"

bool is_in( char c, std::string str );

template <typename T, typename U>
void delete_map( std::map<T, U> & map );

template <typename T>
bool is_in_list( std::list<T> list, T elem );

#endif /* FT_IRC_H */
