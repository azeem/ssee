#include <typeinfo>
#include "Expression.h"
#include "DataTypes.h"
#include "Functions.h"

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

AssignExpr::AssignExpr(Symbol *lh, Expression *rh) {
	lhs = lh;
	rhs = rh;
}

BaseObject *AssignExpr::eval(Environment *env) {
	BaseObject *val;
	val = rhs->eval(env);
	env->set_value(lhs, val);
	return val;
}

IfElseExpr::IfElseExpr(Expression *cond, Expression *if_exp, Expression *else_exp) {
	condition = cond;
	if_expr = if_exp;
	else_expr = else_exp;
}

BaseObject *IfElseExpr::eval(Environment *env) {
	BaseObject *res = condition->eval(env);
	if(typeid(*res) == typeid(Boolean) && *((Boolean *)res) == false)
		return else_expr->eval(env);
	else
		return if_expr->eval(env);
}

BaseObject *LambdaExpr::eval(Environment *env) {
	return (new NonPrimitive(this, env));
}

BaseObject *CallExpr::eval(Environment *env) {
	BaseObject *params[expr_count];
	params[0] = expr_list[0]->eval(env);
	if(!params[0]->is_callable())
		throw ObjectNotCallable();
	for(int i = 1;i < expr_count;i++)
		params[i] = expr_list[i]->eval(env);
	return (((Function *)params[0])->apply(&params[1], expr_count-1));
}
