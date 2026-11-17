#include "LexicalAnalyzer.hpp"
#include "Token.hpp"
#include <iostream>

std::string TypeToString(const Type& type){
    std::string res;

    switch (type) {
    case Type::INT: res = "INT"; break;
    case Type::DOUBLE: res = "DOUBLE"; break;
    case Type::PLUS: res = "PLUS"; break;
    case Type::MINUS: res = "MINUS"; break;
    case Type::MULTIPLY: res = "MULTIPLY"; break;
    case Type::DIVIDE: res = "DIVIDE"; break;
    case Type::LEFTBRACKET: res = "LEFTBRACKET"; break;
    case Type::RIGHTBRACKET: res = "RIGHTBRACKET"; break;
    default: break;
    }

    return res;
}

int main() {
    std::string str;
    std::getline(std::cin, str); //чтобы считать пробел

    std::vector<Token> tokens = LexicalAnalyzer::analyze(str);

    for (size_t i = 0; i < tokens.size(); i++) {
        std::cout << TypeToString(tokens[i].type) << ": " << tokens[i].lex << '\n';
    }

    return 0;
}