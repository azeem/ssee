#include <typeinfo>
#include "Expression.h"
#include "DataTypes.h"

AtomicExpr::AtomicExpr(BaseObject *obj, bool map_sym) {
	object = obj;
	map_symbol = map_sym;
}

BaseObject *AtomicExpr::eval(Environment* env) {
	if(typeid(*object) == typeid(Symbol) && map_symbol)
		return env->get_value((Symbol *)object);
	else
		return object;
}
