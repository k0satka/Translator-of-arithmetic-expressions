#include "PostfixConverter.hpp"
#include <stack>
#include <stdexcept>

namespace {
//классификация токенов
enum class TokenClass { NUMBER, OPERATOR, LEFTBRACKET, RIGHTBRACKET, END, size };
TokenClass classify(const Token& a) {
    if (a.type == Type::INT || a.type == Type::DOUBLE) return TokenClass::NUMBER;
    else if (a.type == Type::PLUS || a.type == Type::MINUS || a.type == Type::MULTIPLY || a.type == Type::DIVIDE) return TokenClass::OPERATOR;
    else if (a.type == Type::LEFTBRACKET) return TokenClass::LEFTBRACKET;
    else if (a.type == Type::RIGHTBRACKET) return TokenClass::RIGHTBRACKET;
    else throw std::invalid_argument("unknown type");
}
//a >= b
bool comparePriority(const Token& a, const Token& b){
    if (a.type == Type::PLUS || a.type == Type::MINUS){
        if (b.type == Type::PLUS || b.type == Type::MINUS) return true;
        return false;
    }
    return true;
}
}

std::vector<Token> PostfixConverter::convert(const std::vector<Token>& tokens) {
    std::vector<Token> res;
    std::stack<Token> stack;

    size_t sz = tokens.size();

    for (size_t i = 0; i <= sz; i++) {
        TokenClass tClass = i < sz ? classify(tokens[i]) : TokenClass::END;

        switch (tClass) {
        case TokenClass::NUMBER: res.push_back(tokens[i]); break;
        case TokenClass::LEFTBRACKET: stack.push(tokens[i]); break;
        case TokenClass::RIGHTBRACKET: 
            while (true) {
                if (stack.empty()) throw std::runtime_error("missing an opening bracket");
                if (stack.top().type == Type::LEFTBRACKET) break;
                res.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
            break;
        case TokenClass::OPERATOR:
            while (!stack.empty() && stack.top().type != Type::LEFTBRACKET && comparePriority(stack.top(), tokens[i])) {
                res.push_back(stack.top());
                stack.pop();
            }
            stack.push(tokens[i]);
            break;
        case TokenClass::END:
            while (!stack.empty()) {
                if (stack.top().type == Type::LEFTBRACKET) throw std::runtime_error("extra opening bracket");
                res.push_back(stack.top());
                stack.pop();
            }
            break;
        default: break;
        }
    }

    return res;
}