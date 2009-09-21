#include "Common.h"
#include "DataTypes.h"

Cons::Cons() {
	first = new None();
	second = new None();
}

Cons::Cons(BaseObject *f, BaseObject *s) {
	first = f;
	second = s;
}

string Cons::str() {
	return ("(" + first->str() + ", " + second->str() + ")");
}

Symbol::Symbol(string srep) {
	str_rep = srep;
}

bool Symbol::operator< (Symbol &sym) {
	return str_rep < sym.str_rep;
}

string Symbol::str() {
	return str_rep;
}


String::String(string val) {
	str_val = val;
}

string String::str() {
	return ("\"" + str_val + "\"");
}

Integer::Integer(long val) {
	int_val = val;
}

string Integer::str() {
	stringstream ss;
	ss << int_val;
	return ss.str();
}
