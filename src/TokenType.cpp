#include "TokenType.hpp"

namespace {
    //таблица с информацией
    constexpr OperatorInfo table[OpCount] = { //priority, arity, asociativity
        /*PLUS*/ {1, 2, Associativity::LEFT},
        /*MINUS*/ {1, 2, Associativity::LEFT},
        /*MULTIPLY*/ {2, 2, Associativity::LEFT},
        /*DIVIDE*/ {2, 2, Associativity::LEFT},
        /*POW*/ {3, 2, Associativity::RIGHT},
    };
}

TokenClass classify(Type type) {
    switch (type) {
        case Type::INT:
        case Type::DOUBLE: return TokenClass::NUMBER;

        case Type::PLUS:
        case Type::MINUS:
        case Type::MULTIPLY:
        case Type::POW:
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