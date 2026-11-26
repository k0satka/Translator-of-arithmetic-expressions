#include "PostfixConverter.hpp"

#include <stack>
#include <stdexcept>

namespace {
//условие извлечения операторов из стека. Здесь влияет приоритет и ассоциативность
bool shouldPopOperator(Type top, Type cur) {
    if (top == Type::LEFTBRACKET) return false;

    OperatorInfo topInf = getOperatorInfo(top);
    OperatorInfo curInf = getOperatorInfo(cur);

    if (topInf.priority > curInf.priority) return true;
    if (topInf.priority == curInf.priority && curInf.associativity == Associativity::LEFT) return true;

    return false;
}
}

std::vector<Token> PostfixConverter::convert(const std::vector<Token>& tokens) {
    std::vector<Token> res;
    std::stack<Token> stack;

    size_t sz = tokens.size();

    for (size_t i = 0; i <= sz; i++) {
        TokenClass tClass = i < sz ? classify(tokens[i].type) : TokenClass::END;

        switch (tClass) {
        case TokenClass::NUMBER: res.push_back(tokens[i]); break;
        case TokenClass::LEFTBRACKET: stack.push(tokens[i]); break;
        case TokenClass::RIGHTBRACKET: 
            while (true) {
                if (stack.empty()) throw PostfixError("unexpected closing parenthesis", tokens[i].pos);
                if (stack.top().type == Type::LEFTBRACKET) break;
                res.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
            break;

        case TokenClass::OPERATOR:
            while (!stack.empty() && shouldPopOperator(stack.top().type, tokens[i].type)) {
                res.push_back(stack.top());
                stack.pop();
            }
            stack.push(tokens[i]);
            break;

        case TokenClass::END:
            while (!stack.empty()) {
                if (stack.top().type == Type::LEFTBRACKET) throw PostfixError("unclosed opening parenthesis", stack.top().pos);
                res.push_back(stack.top());
                stack.pop();
            }
            break;
            
        default: break;
        }
    }

    return res;
}