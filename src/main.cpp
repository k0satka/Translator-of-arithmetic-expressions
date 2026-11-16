#include "LexicalAnalyzer.hpp"
#include "Token.hpp"
#include <iostream>

int main() {
    Token a{Type::NUMBER, "2"};

    std::cout << a.lex;
    
    return 0;
}