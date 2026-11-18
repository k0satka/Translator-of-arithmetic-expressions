#include "Evaluator.hpp"
#include <stack>
#include <stdexcept>

double Evaluator::evaluate(const std::vector<Token>& tokens) {
    std::stack<double> stack;

    size_t sz = tokens.size();
    for (size_t i = 0; i < sz; i++) {
        switch (tokens[i].type) {
            case Type::INT: {
                double a = std::stod(tokens[i].lex);
                stack.push(a);
                break;
            }

            case Type::DOUBLE: {
                double a = std::stod(tokens[i].lex);
                stack.push(a);
                break;
            }

            case Type::DIVIDE: {
                if (stack.size() < 2) throw std::runtime_error("evaluator error: there are not enough operands"); //в стеке не хватает операднов

                double right = stack.top();
                stack.pop();
                double left = stack.top();
                stack.pop();

                if (right == 0.0) throw std::runtime_error("evaluator error: division by zero");
                stack.push(left / right);

                break;
            }

            case Type::PLUS: {
                if (stack.size() < 2) throw std::runtime_error("evaluator error: there are not enough operands"); //в стеке не хватает операднов

                double right = stack.top();
                stack.pop();
                double left = stack.top();
                stack.pop();

                stack.push(left + right);

                break;
            }

            case Type::MINUS: {
                if (stack.size() < 2) throw std::runtime_error("evaluator error: there are not enough operands"); //в стеке не хватает операднов

                double right = stack.top();
                stack.pop();
                double left = stack.top();
                stack.pop();

                stack.push(left - right);

                break;
            }

            case Type::MULTIPLY: {
                if (stack.size() < 2) throw std::runtime_error("evaluator error: there are not enough operands"); //в стеке не хватает операднов

                double right = stack.top();
                stack.pop();
                double left = stack.top();
                stack.pop();

                stack.push(left * right);

                break;
            }
            
            default: throw std::runtime_error("evaluator error: incorrect token type");
        }
    }

    if (stack.size() != 1) throw std::runtime_error("evaluator error");
    return stack.top();
}