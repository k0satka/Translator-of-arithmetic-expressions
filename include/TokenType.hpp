#pragma once

#include <stdexcept>

//типы токенов
enum class Type { PLUS, MINUS, MULTIPLY, DIVIDE, POW, UNARY_PLUS, UNARY_MINUS, ASSIGN, INT, DOUBLE, IDENTIFIER, LEFTBRACKET, RIGHTBRACKET, size };
constexpr size_t OpCount = 8; //кол-во операторов

//классификации токенов
enum class TokenClass { NUMBER, OPERATOR, IDENTIFIER, LEFTBRACKET, RIGHTBRACKET, END, size };
TokenClass classify(Type type);

//информация об операторе
enum class Associativity { LEFT, RIGHT };

struct OperatorInfo {
    int priority;
    size_t arity;
    Associativity associativity;
};

bool isOperator(Type type);

OperatorInfo getOperatorInfo(Type type);