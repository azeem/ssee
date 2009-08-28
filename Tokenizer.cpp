#include "Tokenizer.h"

using namespace std;

TokenType Tokenizer::tokenize() {
// Reads Character from stream, identifies token and returns a TokenType value
// END and ERROR TokenTypes indicate end of stream and erroneous condition
// respectively
	int c;

	token_val = "";
	while (c = stream.get(), stream.good() && isspace(c)); // Skip whitespaces

	if(stream.eof())
		return END;
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
			return ERROR; // Unexpected end of string
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
		return ERROR;
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
	if((isalnum(c) || ispunct(c)) && c != '(' && c != ')' && c != '"')
		return true;
	else
		return false;
}
