#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include "DataTypes.h"
#include "Common.h"

struct SymbolCompare {
// Compare class for SymbolMaps
	bool operator() (Symbol* const&, Symbol* const&);
};
inline bool SymbolCompare::operator() (Symbol* const& lhs, Symbol* const& rhs) {return ((*lhs) < (*rhs));}

// SymbolMap is a std::map that maps Symbol* to BaseObject*
typedef std::map<Symbol*, BaseObject*, SymbolCompare, gc_allocator<std::pair<Symbol*, BaseObject*> > > SymbolMap;

//! Environment maps identifiers to data objects
class Environment : public gc {
	public:
		Environment();
		Environment(Environment*);
		BaseObject *get_value(Symbol*);
		void set_value(Symbol*, BaseObject*);
	private:
		Environment *parent;
		SymbolMap sym_map;
};
inline Environment::Environment() {parent = NULL;}
inline Environment::Environment(Environment *par) {parent = par;}

//! UndefinedIdentifier Exception thrown when search for identifier
//! in an Environment and all of its parents fails
class UndefinedIdentifier : public BaseException {
	private:
		Symbol *identifier;
	public:
		UndefinedIdentifier(Symbol *identifier) : identifier(identifier) {}
		Symbol *get_identifier();
};
inline Symbol *UndefinedIdentifier::get_identifier() {return identifier;}

#endif
