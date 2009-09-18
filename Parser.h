#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include "Common.h"
#include "DataTypes.h"
#include "Tokenizer.h"

class Parser : public gc {
// Parser parses input from a stream into expression objects
	public:
		Parser(std::istream&);
		Cons *tokens_to_list();
	private:
		Tokenizer *tokenizer;
};

#endif
