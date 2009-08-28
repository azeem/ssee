#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <istream>
#include <string>
#include <gc_cpp.h>

enum TokenType {
	BRACKET_OPEN,
	BRACKET_CLOSE,
	STRING,
	INTEGER,
	SYMBOL,
	ERROR,
	END
};

class Tokenizer : public gc {
	public:
		Tokenizer(std::istream&);
		TokenType tokenize();
		std::string token_value();
	private:
		bool check_int();
		bool is_normal_char(int);
		std::istream& stream;
		std::string token_val;
};


inline Tokenizer::Tokenizer(std::istream &str) : stream(str) {token_val = "";}
inline std::string Tokenizer::token_value() {return token_val;}
#endif
