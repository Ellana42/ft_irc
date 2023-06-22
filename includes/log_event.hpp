#ifndef LOG_EVENT_H
#define LOG_EVENT_H

#define LOG_OFF 0
#define LOG_ERROR 1
#define LOG_WARNING 2
#define LOG_INFO 3

#define LOG_LEVEL 3


#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include "Colors.h"

namespace log_event
{
void info( std::string msg );
void warn( std::string msg );
void warn( std::string msg, std::string command );
void error( std::string msg );
void reply( int socket, std::string msg );
void command( int socket, std::string command );
std::string get_formatted_command( std::string command );

template <typename T>
void info( std::string msg, T detail )
{
	if ( LOG_LEVEL < LOG_INFO )
	{
		return;
	}
	std::stringstream ss;

	ss << RESET "[INFO] " << msg << " " << detail << RESET;
	std::cerr << ss.str() << std::endl;
}

template <typename T>
void warn( std::string msg, T detail )
{
	if ( LOG_LEVEL < LOG_WARNING )
	{
		return;
	}
	std::stringstream ss;

	ss << YELLOW "[WARN] " << msg << " " << detail << RESET;
	std::cerr << ss.str() << std::endl;
}
}
#endif /* LOG_EVENT_H */
