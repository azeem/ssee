#include <iostream>
#include <DataTypes.h>

int main() {
	None *no      = new None();
	Symbol *sym1  = new Symbol("hello");
	Symbol *sym2  = new Symbol("how-are-you");
	Cons *pair    = new Cons(sym1, sym2);
	String *str   = new String("hello World!!");
	Integer *intg = new Integer(458);
	Boolean *tval = new Boolean(true);

	std::cout << "None Object : " << no->str() << std::endl;
	std::cout << "Symbol Object : " << sym1->str() << std::endl;
	std::cout << "Cons Object : " << pair->str() << std::endl;
	std::cout << "String object : " << str->str() << std::endl;
	std::cout << "Integer object : " << intg->str() << std::endl;
	std::cout << "Boolean object : " << tval->str() << std::endl;

	return 0;
}
