#include <istream>
#include <stack>
#include <cstdlib>
#include "Parser.h"
#include "Tokenizer.h"
#include "DataTypes.h"

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
				Integer *intgr = new Integer(atol(tokenizer->token_value().c_str()));
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
					return NULL;
				else
					return new Cons();
				break;
			case ERROR:
				return NULL;
		}
	}
	return (Cons *)mystack.top();
}
