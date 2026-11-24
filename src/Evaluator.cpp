#include "Evaluator.hpp"
#include <stack>
#include <stdexcept>

double Evaluator::evaluate(const std::vector<Token>& tokens) {
    std::stack<double> stack;

    size_t sz = tokens.size();
    for (size_t i = 0; i < sz; i++) {
        switch (tokens[i].type) {
            case Type::INT:
            case Type::DOUBLE: {
                double a = std::stod(tokens[i].lex);
                stack.push(a);
                break;
            }

            case Type::PLUS:
            case Type::MINUS:
            case Type::MULTIPLY:
            case Type::DIVIDE: {
                if (stack.size() < 2) throw std::runtime_error("evaluator error: there are not enough operands"); //в стеке не хватает операднов

                double right = stack.top();
                stack.pop();
                double left = stack.top();
                stack.pop();

                switch (tokens[i].type) {
                    case Type::DIVIDE:
                        if (right == 0.0) throw std::runtime_error("evaluator error: division by zero");
                        stack.push(left / right);
                        break;
                    case Type::PLUS:
                        stack.push(left + right);
                        break;
                    case Type::MINUS:
                        stack.push(left - right);
                        break;
                    case Type::MULTIPLY:
                        stack.push(left * right);
                        break;
                    default: throw std::runtime_error("evaluator error: incorrect token type");
                }
                break;
            }
            default: throw std::runtime_error("evaluator error: incorrect token type");
        }
    }

    if (stack.size() != 1) throw std::runtime_error("evaluator error");
    return stack.top();
}