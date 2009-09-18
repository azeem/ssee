#include "Parser.h"
#include "Common.h"
#include <iostream>

int main() {
	stringstream stream("(+ a b (- b 12))");
	Parser par(stream);
	Cons *res = par.tokens_to_list();
	std::cout << res->str();
	return 0;
}
