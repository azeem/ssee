#include "Parser.h"
#include "Common.h"
#include "DataTypes.h"
#include <iostream>

int main() {
	stringstream stream("(= a 23)");
	Parser par(stream);
	Cons *res = par.tokens_to_list();
	Expression *expr = par.parse_to_expression(res);
	Environment *env = new Environment();

	std::cout << expr->eval(env)->str() << std::endl;

	env->set_value(new Symbol("val"), new Boolean(false));
	stream.str("(if val (if a 1 2) \"hello\")");
	res = par.tokens_to_list();
	expr = par.parse_to_expression(res);
	std::cout << expr->eval(env)->str() << std::endl;
	return 0;
}
