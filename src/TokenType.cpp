#include "TokenType.hpp"

namespace {
    //таблица с информацией
    OperatorInfo table[OpCount] = { //priority, arity
        /*PLUS*/ {1, 2},
        /*MINUS*/ {1, 2},
        /*MULTIPLY*/ {2, 2},
        /*DIVIDE*/ {2, 2},
    };
}

TokenClass classify(Type type) {
    switch (type) {
        case Type::INT:
        case Type::DOUBLE: return TokenClass::NUMBER;

        case Type::PLUS:
        case Type::MINUS:
        case Type::MULTIPLY:
        case Type::DIVIDE: return TokenClass::OPERATOR;

        case Type::LEFTBRACKET: return TokenClass::LEFTBRACKET;
        case Type::RIGHTBRACKET: return TokenClass::RIGHTBRACKET;

        default: throw std::invalid_argument("unknown type");
    }
}

bool isOperator(Type type) {
    return static_cast<size_t>(type) < OpCount;
}

OperatorInfo getOperatorInfo(Type type) {
    //достаём из таблицы информацию о типе
    if (static_cast<size_t>(type) >= OpCount) throw std::invalid_argument("unknown type");
    
    return table[static_cast<size_t>(type)];
}