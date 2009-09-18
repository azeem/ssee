#include <iostream>
#include <DataTypes.h>

using namespace std;

int main() {
	None *no      = new None();
	Symbol *sym1  = new Symbol("hello");
	Symbol *sym2  = new Symbol("how-are-you");
	Cons *pair    = new Cons(sym1, sym2);
	String *str   = new String("hello World!!");
	Integer *intg = new Integer(458);

	cout << "None Object : " << no->str() << endl;
	cout << "Symbol Object : " << sym1->str() << endl;
	cout << "Cons Object : " << pair->str() << endl;
	cout << "String object : " << str->str() << endl;
	cout << "Integer object : " << intg->str() << endl;

	return 0;
}
