#ifndef MODE_PARSING_H
#define MODE_PARSING_H

#include "ft_irc.hpp"

enum state {PlusMinus, ModeChar};
enum type {Plus, Minus};

class ModeParsing
{
	private:
		std::string modestring;

		state current_state;
		type current_type;
		std::string added_modes;
		std::string removed_modes;

		unsigned int position;

		char get_char( void );
		void parse_mode_char( void );
		void parse_plus_minus( void );

	public:
		ModeParsing( std::string modestring );
		virtual ~ModeParsing();
		void parse( void );
		std::string get_added_modes( void );
		std::string get_removed_modes( void );
		void move( void );

		class InvalidModestringException : public std::exception {};
};

#endif /* MODE_PARSING_H */
