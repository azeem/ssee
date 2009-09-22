#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Common.h"
#include "Environment.h"

class Expression : public gc {
	public:
		virtual BaseObject *eval(Environment*) = 0;
};

class AtomicExpr : public Expression {
	private:
		BaseObject *object;
		bool map_symbol;
	public:
		AtomicExpr(BaseObject*, bool map_sym = true);
		BaseObject *eval(Environment*);
};

class AssignExpr : public Expression {
	private:
		Symbol *lhs;
		Expression *rhs;
	public:
		AssignExpr(Symbol*, Expression*);
		BaseObject *eval(Environment*);
};

class IfElseExpr : public Expression {
	private:
		Expression *condition;
		Expression *if_expr;
		Expression *else_expr;
	public:
		IfElseExpr(Expression*, Expression*, Expression*);
		BaseObject *eval(Environment*);
};

#endif
