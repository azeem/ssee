#include "Common.h"
#include "Parser.h"
#include "Expression.h"
#include "Functions.h"
#include "DataTypes.h"
#include <iostream>

Environment *init_env() {
	Environment *env = new Environment();
	env->set_value(new Symbol("+"), new IntAdd(env));
	env->set_value(new Symbol("-"), new IntSub(env));
	env->set_value(new Symbol("*"), new IntMul(env));
	env->set_value(new Symbol("=="), new IntEq(env));
	env->set_value(new Symbol("car"), new ConsCar(env));
	env->set_value(new Symbol("cdr"), new ConsCdr(env));
	env->set_value(new Symbol("load"), new LoadFile(env));
	env->set_value(new Symbol("print"), new PrintLine(env));
	env->set_value(new Symbol("exit"), new ExitRepl(env));
	env->set_value(new Symbol("true"), new Boolean(true));
	env->set_value(new Symbol("false"), new Boolean(false));
	env->set_value(new Symbol("none"), new None());
	return env;
}

int main() {
	//stringstream str("(load \"test.se\")");
	Parser par(std::cin);
	//Parser par(str);
	Expression *expr;
	BaseObject *res;
	Environment *env = init_env();
	std::cout << std::endl
			  << "\tSimple Symbolic Expression Evaluator"<< std::endl
			  << "\tAzeem Arshad      Kevin Jacob Kurian" << std::endl
			  << "\t     SCT College Of Engineering" << std::endl
			  << std::endl
			  << "Type (exit) to exit" << std::endl;
	while(true) {
		std::cout << "> ";
		try {
			expr = par.parse();
			if(!expr)
				break;
			res = expr->eval(env);
			if(typeid(*res) != typeid(None))
				std::cout << res->str() << std::endl;
		}
		catch(ParamCountMismatch &e) {
			std::cout << "Error: Function expects " 
					  << (e.get_atleast()?"atleast ":"")
					  << e.get_expecting()
					  << " arguments, given "
					  << e.get_given() << std::endl;
		}
		catch(ParamTypeMismatch &e) {
			std::cout << "Error: Invalid argument type" << std::endl;
		}
		catch(CannotConvertToInt &e) {
			std::cout << "Error: Cannot convert object to Integer" << std::endl;
		}
		catch(UndefinedIdentifier &e) {
			std::cout << "Error: Symbol \"" << e.get_identifier()->str()
					  << "\" is not defined in this Environment" << std::endl;
		}
		catch(ObjectNotCallable &e) {
			std::cout << "Error: Object cannot be used in a function call" << std::endl;
		}
		catch(SyntaxError &e) {
			std::cout << "Error: Bad Syntax" << std::endl;
		}
		catch(UnexpectedEnd &e) {
			std::cout << "Error: Parser reached the end of stream unexpectedly" << std::endl;
		}
		catch(UnmatchedParanthesis &e) {
			std::cout << "Error: Expression contains an unmatched paranthesis" << std::endl;
		}
	}
	return 0;
}
