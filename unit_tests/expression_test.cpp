#include <iostream>
#include "Expression.h"
#include "Environment.h"

int main() {
	Symbol *sym1 = new Symbol("my-sym");
	Symbol *sym2 = new Symbol("hello");
	Integer *intgr = new Integer(123);
	Cons *pair = new Cons(new String("this is a string"), new Integer(78));
	Environment *env = new Environment();

	AtomicExpr *aexp = new AtomicExpr(sym1);
	AtomicExpr *aexp2 = new AtomicExpr(sym2, false);
	AtomicExpr *aexp3 = new AtomicExpr(pair);

	env->set_value(sym1, intgr);

	std::cout << "Expression 1 : " << aexp->eval(env)->str() << std::endl;
	std::cout << "Expression 2 : " << aexp2->eval(env)->str() << std::endl;
	std::cout << "Expression 3 : " << aexp3->eval(env)->str() << std::endl;

	return 0;
}
