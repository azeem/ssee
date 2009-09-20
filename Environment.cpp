#include "Environment.h"

BaseObject *Environment::get_value(Symbol *id) {
// Finds value corresponding to an identifier in this
// Environment or any of its parents. Throws UndefinedIdentifier
// error if identifier cannot be found
	SymbolMap::iterator it;
	it = sym_map.find(id);
	if(it == sym_map.end()) {
		if(parent == NULL)
			throw UndefinedIdentifier(id);
		else
			return parent->get_value(id);
	}
	else
		return (*it).second;
}

void Environment::set_value(Symbol *id, BaseObject *value) {
// sets value of identifier
	sym_map[id] = value;
}
