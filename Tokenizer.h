#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <istream>
#include "Common.h"

enum TokenType {
	COMMENT,
	BRACKET_OPEN,
	BRACKET_CLOSE,
	STRING,
	INTEGER,
	SYMBOL,
	END
};

//! Tokenizer identifies tokens from any stream input
class Tokenizer : public gc {
	public:
		Tokenizer(std::istream&);
		TokenType tokenize();
		string token_value();
	private:
		bool check_int();
		bool is_normal_char(int);
		std::istream& stream;
		string token_val;
};


inline Tokenizer::Tokenizer(std::istream &str) : stream(str) {token_val = "";}
inline string Tokenizer::token_value() {return token_val;}

class UnknownTokenType : public BaseException {};
class UnterminatedString : public BaseException {};
#endif
