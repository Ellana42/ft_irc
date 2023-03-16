#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "ft_irc.hpp"

enum State {Param, Space, LongParam};

class Tokenizer
{
	private:

		std::string content;
		std::vector<std::string> tokens;
		State state;
		unsigned int current_position;

		std::string buffer;

		void tokenize_param( void );
		void tokenize_space( void );
		void tokenize_long_param( void );
		char current_char( void ) const;
		void accumulate( void );
		void push_token( void );
		void move( void );

	public:
		Tokenizer( std::string content );
		virtual ~Tokenizer();
		void tokenize( void );
		void change_state( State new_state );
		std::vector<std::string> get_tokens( void );
};

#endif /* TOKENIZER_H */
