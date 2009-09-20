#include <iostream>
#include "DataTypes.h"
#include "Environment.h"

int main() {
	Symbol *ids[3];
	BaseObject *vals[3];
	Environment *env[2];

	ids[0] = new Symbol("a");
	ids[1] = new Symbol("my-name");
	ids[2] = new Symbol("the-name");

	vals[0] = new Integer(123);
	vals[1] = new String("This is a string");
	vals[2] = new Cons(new Integer(12), new Integer(34));
	env[0] = new Environment();
	env[1] = new Environment(env[0]);

	env[0]->set_value(ids[0], vals[0]);
	env[0]->set_value(ids[1], vals[1]);
	env[1]->set_value(ids[2], vals[2]);

	for(int j = 0;j < 2;j++) {
		std::cout << "env " << j << std::endl;
		for(int i = 0;i < 3;i++) {
			try {
				std::cout << ids[i]->str() << " = " << env[j]->get_value(ids[i])->str() << std::endl;
			}
			catch(UndefinedIdentifier &e) {
				std::cout << "Reference to undefined identifier : " << e.identifier->str() << std::endl;
			}
		}
	}

	return 0;
}
