#pragma once

#include <stdexcept>

//типы токенов
enum class Type { PLUS, MINUS, MULTIPLY, DIVIDE, POW, INT, DOUBLE, LEFTBRACKET, RIGHTBRACKET, size };
constexpr size_t OpCount = 5; //кол-во операторов

//классификации токенов
enum class TokenClass { NUMBER, OPERATOR, LEFTBRACKET, RIGHTBRACKET, END, size };
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