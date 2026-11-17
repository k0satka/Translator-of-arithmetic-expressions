#pragma once
#include <string>

enum class Type { INT, DOUBLE, PLUS, MINUS, MULTIPLY, DIVIDE, LEFTBRACKET, RIGHTBRACKET };

struct Token {
    Type type;
    std::string lex;
};