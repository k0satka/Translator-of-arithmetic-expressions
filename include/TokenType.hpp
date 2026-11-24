#pragma once

#include <stdexcept>

//типы токенов
enum class Type { PLUS, MINUS, MULTIPLY, DIVIDE, INT, DOUBLE, LEFTBRACKET, RIGHTBRACKET, size };
constexpr size_t OpCount = 4; //кол-во операторов

//классификации токенов
enum class TokenClass { NUMBER, OPERATOR, LEFTBRACKET, RIGHTBRACKET, END, size };
TokenClass classify(Type type);

//информация об операторе
struct OperatorInfo {
    int priority;
    size_t arity;
};

bool isOperator(Type type);

OperatorInfo getOperatorInfo(Type type);