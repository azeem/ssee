#include <iostream>
#include "Common.h"
#include "Tokenizer.h"

int main() {
	stringstream stream("(+ a b 56 \"Hello \\\"World\\\"!!\")");
    Tokenizer t(stream);
    TokenType tt;
    while(tt = t.tokenize(), tt != END) {
    	switch(tt) {
    		case BRACKET_OPEN :std::cout << "Opening Bracket" << std::endl; break;
    		case BRACKET_CLOSE:std::cout << "Closing Bracket" << std::endl; break;
    		case STRING :std::cout << "String (\"" << t.token_value() << "\")" << std::endl; break;
    		case INTEGER:std::cout << "Integer (\"" << t.token_value() << "\")" << std::endl; break;
    		case SYMBOL :std::cout << "Symbol (\"" << t.token_value() << "\")" << std::endl; break;
    		case ERROR  :std::cout << "Error!!" << std::endl;
			case END    :break;
    	}
    }
    return 0;
}
