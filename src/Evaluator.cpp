#include "Evaluator.hpp"

#include <stack>
#include <stdexcept>
#include <cmath>

double Evaluator::evaluate(const std::vector<Token>& tokens) {
    std::stack<double> stack;

    size_t sz = tokens.size();
    for (size_t i = 0; i < sz; i++) {
        switch (classify(tokens[i].type)) {
            case TokenClass::NUMBER: {
                double a;
                try { 
                    size_t processed = 0; //сколько символов обработано
                    a = std::stod(tokens[i].lex, &processed); 
                    if (processed != tokens[i].lex.size()) throw std::exception("stod error");
                }
                catch (const std::exception& e) { throw EvaluatorError(std::string(e.what()), tokens[i].pos); }
                stack.push(a);
                break;
            }

            case TokenClass::OPERATOR: {
                //извлечение операндов (будет зависить от арности)
                if (stack.size() < 2) throw EvaluatorError("not enough operands", tokens[i].pos); //в стеке не хватает операднов

                double right = stack.top();
                stack.pop();
                double left = stack.top();
                stack.pop();
                
                //вычисление
                switch (tokens[i].type) {
                    case Type::DIVIDE:
                        if (right == 0.0) throw EvaluatorError("division by zero", tokens[i].pos);
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
                    case Type::POW:
                        stack.push(std::pow(left, right));
                        break;
                    default: throw EvaluatorError("incorrect operator type", tokens[i].pos);
                }
                break;
            }
            default: throw EvaluatorError("unexpected token", tokens[i].pos);
        }
    }

    if (stack.size() != 1) throw EvaluatorError("invalid postfix expression", std::string::npos);
    return stack.top();
}