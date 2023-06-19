#include "signal.hpp"
#include <iostream>

bool sig::stopServer = false;

void sig::signalHandler( int signum )
{
	/* std::cout << "[Sig Handler] Caught signal " << signum << std::endl; */
	if ( signum == SIGINT )
	{
		sig::stopServer = true;
	}
}
