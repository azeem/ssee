#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include "Common.h"
#include "DataTypes.h"
#include "Tokenizer.h"
#include "Expression.h"

//! Parser class is used parse input from a stream into expression objects
class Parser : public gc {
	public:
		Parser(std::istream&);
		Cons *tokens_to_list();
		Expression **parse_to_expression_list(Cons*, int&);
		Expression *parse_to_expression(BaseObject*);
		Expression **parse_till_end(int &count);
		Expression *parse();
	private:
		Tokenizer *tokenizer;
};

class UnexpectedEnd : public BaseException {};
class UnknownToken : public BaseException {};
class UnmatchedParanthesis : public BaseException {};
class SyntaxError : public BaseException {};
#endif
