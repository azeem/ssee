#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include "Common.h"
#include "DataTypes.h"
#include "Tokenizer.h"
#include "Expression.h"

class Parser : public gc {
// Parser parses input from a stream into expression objects
	public:
		Parser(std::istream&);
		Cons *tokens_to_list();
		Expression *parse_to_expression(BaseObject *);
	private:
		Tokenizer *tokenizer;
};

class UnexpectedEnd : public BaseException {};
class UnknownToken : public BaseException {};
class SyntaxError : public BaseException {};
#endif
