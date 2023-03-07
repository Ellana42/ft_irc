#ifndef APPLICATION_H
#define APPLICATION_H

#include "Context.hpp"

class Application
{
	private:
		int	socket;
		Context *context;

	public:
		Application();
		Application( const Application & src );
		Application & operator=( const Application & rhs );
		virtual ~Application();

		void client_timeout_check( void ); // Separate class
		void listen( void ); // transmit to context ?
};

#endif /* APPLICATION_H */
