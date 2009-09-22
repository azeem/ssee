#include <typeinfo>
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

unsigned long Cons::list_length() {
	Cons *cur_pair = this;
	BaseObject *cadr;
	unsigned long count = 1;
	while(true) {
		cadr = cur_pair->cdr();
		if(typeid(*cadr) != typeid(Cons))
			break;
		cur_pair = (Cons *)cadr;
		count++;
	}
	return count;
}

Symbol::Symbol(string srep) {
	str_rep = srep;
}

bool Symbol::operator< (Symbol &sym) {
	return str_rep < sym.str_rep;
}

bool Symbol::operator== (const char *str) {
	return (str_rep == str);
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

Boolean::Boolean(bool tval) {
	truth_val = tval;
}

string Boolean::str() {
	if(truth_val)
		return "True";
	else
		return "False";
}

bool Boolean::truth() {
	return truth_val;
}

bool Boolean::operator== (bool val) {
	return truth_val == val;
}
