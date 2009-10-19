#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Common.h"
#include "Environment.h"

//! Expressions type represents a Symbolic Expression
class Expression : public gc {
	public:
		virtual BaseObject *eval(Environment*) = 0;
};

//! AtomicExpr represents Atomic expression which evaluate
//! to the data they hold
class AtomicExpr : public Expression {
	private:
		BaseObject *object;
		bool map_symbol;
	public:
		AtomicExpr(BaseObject*, bool map_sym = true);
		BaseObject *eval(Environment*);
};

//! AssignExpr is used to map symbols to object during runtime
class AssignExpr : public Expression {
	private:
		Symbol *lhs;
		Expression *rhs;
	public:
		AssignExpr(Symbol*, Expression*);
		BaseObject *eval(Environment*);
};

//! IfElseExpr allows conditional evaluation
class IfElseExpr : public Expression {
	private:
		Expression *condition;
		Expression *if_expr;
		Expression *else_expr;
	public:
		IfElseExpr(Expression*, Expression*, Expression*);
		BaseObject *eval(Environment*);
};

//! LambdaExpr allows the creation on NonPrimitve Functions at runtime
class LambdaExpr : public Expression {
	private:
		Symbol **param_list;
		Expression **expr_list;
		int param_count;
		int expr_count;
	public:
		LambdaExpr(Symbol **param_list, int param_count, Expression **expr_list, int expr_count):
			param_list(param_list),
			expr_list(expr_list),
			param_count(param_count),
			expr_count(expr_count) {}
		Symbol **get_param_list();
		Expression **get_expr_list();
		int get_param_count();
		int get_expr_count();
		BaseObject *eval(Environment*);
};
inline Symbol **LambdaExpr::get_param_list() {return param_list;}
inline int LambdaExpr::get_param_count() {return param_count;}
inline Expression **LambdaExpr::get_expr_list() {return expr_list;}
inline int LambdaExpr::get_expr_count() {return expr_count;}


//! CallExpr represents a function call. They evaluate to the result of the
//! function call
class CallExpr : public Expression {
	private:
		Expression **expr_list;
		int expr_count;
	public:
		CallExpr(Expression **expr_list, int expr_count):
			expr_list(expr_list),
			expr_count(expr_count) {}
		BaseObject *eval(Environment*);
};

//! ObjectNotCallable Exception is thrown when the first item
//! in a CallExpr is not a valid function
class ObjectNotCallable : public BaseException {};

#endif
