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

	while(true) {
		while(token_type = tokenizer->tokenize(), token_type == COMMENT);
		switch(token_type) {
			case BRACKET_OPEN:
				mystack.push(NULL);
				break;
			case BRACKET_CLOSE: {
				BaseObject *obj;
				Cons *pair = NULL;
				while(true) {
					if(mystack.size() == 0)
						throw UnmatchedParanthesis();
					obj = mystack.top();
					mystack.pop();
					if(obj == NULL)
						break;
					if(!pair)
						pair = new Cons(obj, new None());
					else
						pair = new Cons(obj, pair);
				}
				if(!pair)
					mystack.push(new None());
				else
					mystack.push(pair);
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
		if(mystack.size() == 1 && mystack.top() != NULL)
			break;
	}
	return (Cons *)mystack.top();
}

Expression **Parser::parse_to_expression_list(Cons *list, int &count) {
	count = list->list_length();
	Expression **expr_list = new (GC) Expression*[count];
	for(int i = 0;i < count;i++) {
		expr_list[i] = parse_to_expression(list->car());
		list = (Cons *)list->cdr();
	}
	return expr_list;
}

Expression *Parser::parse_to_expression(BaseObject *obj) {
	if(typeid(*obj) != typeid(Cons))
		return new AtomicExpr(obj);

	Cons *expr = (Cons *)obj;
	if(typeid(*expr->car()) == typeid(Symbol)) {
		Symbol *first_sym = (Symbol *)expr->car();
		if(*first_sym == "=") {
			if(expr->list_length() != 3 && typeid(*expr->car()) != typeid(Symbol))
				throw SyntaxError();
			else {
				expr = (Cons *)expr->cdr();
				Symbol *lhs = (Symbol *)expr->car();
				expr = (Cons *)expr->cdr();
				Expression *rhs = parse_to_expression(expr->car());
				return (new AssignExpr(lhs, rhs));
			}
		}
		else if(*first_sym == "if") {
			if(expr->list_length() != 4)
				throw SyntaxError();
			else {
				expr = (Cons *)expr->cdr();
				Expression *condition = parse_to_expression(expr->car());
				expr = (Cons *)expr->cdr();
				Expression *if_expr = parse_to_expression(expr->car());
				expr = (Cons *)expr->cdr();
				Expression *else_expr = parse_to_expression(expr->car());
				return (new IfElseExpr(condition, if_expr, else_expr));
			}
		}
		else if(*first_sym == "quote") {
			if(expr->list_length() != 2)
				throw SyntaxError();
			else {
				expr = (Cons *)expr->cdr();
				return (new AtomicExpr(expr->car(), false));
			}
		}
		else if(*first_sym == "lambda") {
			if(expr->list_length() < 3)
				throw SyntaxError();
			expr = (Cons *)expr->cdr();
			Symbol **param_list;
			int param_count = 0;
			if(typeid(*expr->car()) == typeid(None))
				param_list = NULL;
			else {
				Cons *list = (Cons *)expr->car();
				param_list = new (GC) Symbol*[list->list_length()];
				while(true) {
					if(typeid(*list->car()) != typeid(Symbol))
						throw SyntaxError();
					param_list[param_count++] = (Symbol *)list->car();
					if(typeid(*list->cdr()) == typeid(None))
						break;
					list = (Cons *)list->cdr();
				}
			}
			expr = (Cons *)expr->cdr();
			int expr_count;
			Expression **expr_list = parse_to_expression_list(expr, expr_count);
			return (new LambdaExpr(param_list, param_count, expr_list, expr_count));
		}
	}

//	expr = (Cons *)obj;
	int expr_count;
	Expression **expr_list = parse_to_expression_list(expr, expr_count);
	return (new CallExpr(expr_list, expr_count));
}

Expression **Parser::parse_till_end(int &count) {
	Cons *list = NULL;
	while(true) {
		Cons *token_list = tokens_to_list();
		if(!token_list)
			break;
		if(!list)
			list = new Cons(token_list, new None());
		else
			list = new Cons(token_list, list);
	}
	if(!list)
		return NULL;
	count = list->list_length();
	Expression **expr_list = new (GC) Expression*[count];
	for(int i = count-1;i >= 0;i--) {
		expr_list[i] = parse_to_expression(list->car());
		list = (Cons *)list->cdr();
	}
	return expr_list;
}

Expression *Parser::parse() {
	Cons *list = tokens_to_list();
	if(!list)
		return NULL;
	else
		return parse_to_expression(list);
}
