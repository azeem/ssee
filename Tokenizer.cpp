#include <cctype>
#include "Tokenizer.h"

TokenType Tokenizer::tokenize() {
// Reads Character from stream, identifies token and returns a TokenType value
// throws UnknownTokenType and UnterminatedString exceptions.
	int c;

	token_val = "";
	while (c = stream.get(), stream.good() && isspace(c)); // Skip whitespaces

	if(stream.eof())
		return END;
	else if (c == ';') {
		while(c = stream.get(), stream.good() && c != '\n');
		return COMMENT;
	}
	else if (c == '(')
		return BRACKET_OPEN;
	else if (c == ')')
		return BRACKET_CLOSE;
	else if (c == '"') {
		while (c = stream.get(), stream.good() && c != '"') {
			if(c == '\\') { // Handle Escape Sequence
				c = stream.get();
				if(!stream.good())
					break;
				token_val.push_back(c);
			}
			else
				token_val.push_back(c);
		}
		if(c == '"')
			return STRING;
		else
			throw UnterminatedString();
    }
    else if (is_normal_char(c)) {
    	while(true) {
    		token_val.push_back(c);
    		c = stream.get();
			if(!stream.good())
				break;
			else if(!is_normal_char(c)) {
				stream.unget();
				break;
			}
		}
		if(check_int())
			return INTEGER;
		else
			return SYMBOL;
	}
	else
		throw UnknownTokenType();
}

bool Tokenizer::check_int() {
// Return true if token_val string contains an integer
	for(unsigned int i = 0;i < token_val.length();i++) {
		if(!isdigit(token_val[i]))
			return false;
	}
	return true;
}

bool Tokenizer::is_normal_char(int c) {
// Returns true if c is character that has no special meaning
	if((std::isalnum(c) || std::ispunct(c)) && c != '(' && c != ')' && c != '"')
		return true;
	else
		return false;
}
