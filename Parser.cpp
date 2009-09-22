#include <istream>
#include <iostream>
#include <typeinfo>
#include <stack>
#include <cstdlib>
#include "Parser.h"
#include "Tokenizer.h"
#include "DataTypes.h"
#include "Expression.h"

Parser::Parser(std::istream &stream) {
	tokenizer = new Tokenizer(stream);
}

Cons *Parser::tokens_to_list() {
	std::stack<BaseObject *> mystack;
	TokenType token_type;
	bool flag = true;

	while(flag) {
		token_type = tokenizer->tokenize();
		switch(token_type) {
			case BRACKET_OPEN:
				mystack.push(NULL);
				break;
			case BRACKET_CLOSE: {
				BaseObject *obj;
				BaseObject *second = new None();
				Cons *pair;
				while(true) {
					obj = mystack.top();
					mystack.pop();
					if(obj == NULL)
						break;
					pair = new Cons(obj, second);
					second = pair;
				}
				mystack.push(pair);
				if(mystack.size() == 1)
					flag = false;
				break;
			}
			case STRING: {
				String *str = new String(tokenizer->token_value());
				mystack.push(str);
				break;
			}
			case INTEGER: {
				Integer *intgr = new Integer(std::atol(tokenizer->token_value().c_str()));
				mystack.push(intgr);
				break;
			}
			case SYMBOL: {
				Symbol *sym = new Symbol(tokenizer->token_value());
				mystack.push(sym);
				break;
			}
			case END:
				if(mystack.size() != 0)
					throw UnexpectedEnd();
				else
					return NULL;
				break;
		}
	}
	return (Cons *)mystack.top();
}

Expression *Parser::parse_to_expression(BaseObject *obj) {
	if(typeid(*obj) != typeid(Cons))
		return new AtomicExpr(obj);

	Cons *expr = (Cons *)obj;
	if(typeid(*expr->car()) == typeid(Symbol)) {
		Symbol *first_sym = (Symbol *)expr->car();
		expr = (Cons *)expr->cdr();
		if(*first_sym == "=") {
			if(expr->list_length() != 2 && typeid(*expr->car()) != typeid(Symbol))
				throw SyntaxError();
			else {
				Symbol *lhs = (Symbol *)expr->car();
				expr = (Cons *)expr->cdr();
				Expression *rhs = parse_to_expression(expr->car());
				return (new AssignExpr(lhs, rhs));
			}
		}
		else if(*first_sym == "if") {
			if(expr->list_length() != 3)
				throw SyntaxError();
			else {
				Expression *condition = parse_to_expression(expr->car());
				expr = (Cons *)expr->cdr();
				Expression *if_expr = parse_to_expression(expr->car());
				expr = (Cons *)expr->cdr();
				Expression *else_expr = parse_to_expression(expr->car());
				return (new IfElseExpr(condition, if_expr, else_expr));
			}
		}
	}

	return (new AtomicExpr(obj));
}
