#pragma once
#include <string>

enum class Type { NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, LEFTBRACKET, RIGHTBRACKET };

struct Token {
    Type type;
    std::string lex;
};