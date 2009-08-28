#include <iostream>
#include <sstream>
#include "Tokenizer.h"

using namespace std;

int main() {
	stringstream stream("(+ a b 56 \"Hello \\\"World\\\"!!\")");
    Tokenizer t(stream);
    TokenType tt;
    while(tt = t.tokenize(), tt != END) {
    	switch(tt) {
    		case BRACKET_OPEN :cout << "Opening Bracket" << endl; break;
    		case BRACKET_CLOSE:cout << "Closing Bracket" << endl; break;
    		case STRING :cout << "String (\"" << t.token_value() << "\")" << endl; break;
    		case INTEGER:cout << "Integer (\"" << t.token_value() << "\")" << endl; break;
    		case SYMBOL :cout << "Symbol (\"" << t.token_value() << "\")" << endl; break;
    		case ERROR  :cout << "Error!!" << endl;
    	}
    }
    return 0;
}
