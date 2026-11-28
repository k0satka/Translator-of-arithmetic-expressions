#include "SyntaxAnalyzer.hpp"

#include <stack>
#include <stdexcept>

namespace {
//состояния КА
enum class State { EXP_OPERAND, EXP_OPERATOR, size }; 

//возможные действия
enum class Action { NONE, PUSH, POP, CHECK_STACK, SEND_ERROR, size };

struct Cell {
    State nextState;
    Action action;
};

//таблица с правилами, где по состоянию и токену можно посмотреть следующее состояние и действие
constexpr Cell table[static_cast<size_t>(State::size)][static_cast<size_t>(TokenClass::size)] = {
    /*EXP_OPERAND*/{
        {State::EXP_OPERATOR, Action::NONE}, //number
        {State::EXP_OPERAND, Action::SEND_ERROR}, //operator
        {State::EXP_OPERATOR, Action::NONE}, //identifier
        {State::EXP_OPERAND, Action::PUSH}, //leftbracket
        {State::EXP_OPERAND, Action::SEND_ERROR}, //rightbracket
        {State::EXP_OPERAND, Action::SEND_ERROR}, //end
    },
    /*EXP_OPERATOR*/{
        {State::EXP_OPERATOR, Action::SEND_ERROR}, //number
        {State::EXP_OPERAND, Action::NONE}, //operator
        {State::EXP_OPERATOR, Action::SEND_ERROR}, //identifier
        {State::EXP_OPERATOR, Action::SEND_ERROR}, //leftbracket
        {State::EXP_OPERATOR, Action::POP}, //rightbracket
        {State::EXP_OPERATOR, Action::CHECK_STACK}, //end
    }
};
}

void SyntaxAnalyzer::analyze(const std::vector<Token>& tokens) {
    State state = State::EXP_OPERAND; //начальное состояние
    TokenClass tClass; //тип символа
    std::stack<Token> stack; //для проверки скобок

    size_t i = 0;
    size_t len = tokens.size();

    while (i <= len) {
        tClass = i < len ? classify(tokens[i].type) : TokenClass::END;

        //исключение из правил для унарных +-
        if (i < len && state == State::EXP_OPERAND && (tokens[i].type == Type::PLUS || tokens[i].type == Type::MINUS)) {
            ++i;
            continue;
        }

        Cell toDo = table[static_cast<size_t>(state)][static_cast<size_t>(tClass)];

        switch (toDo.action) {
            case Action::NONE: break;
            case Action::PUSH: stack.push(tokens[i]); break;
            case Action::POP: if (stack.empty()) throw SyntaxError("unexpected closing parenthesis", tokens[i].pos); else stack.pop(); break;
            case Action::CHECK_STACK: if (!stack.empty()) throw SyntaxError("unclosed opening parenthesis", stack.top().pos); break;
            case Action::SEND_ERROR: 
                if (state == State::EXP_OPERAND) {
                    if (tokens.empty()) throw SyntaxError("expected operand", 0);
                    if (i == len) throw SyntaxError("expected operand", tokens.back().pos == std::string::npos ? tokens.back().pos : tokens.back().pos + tokens.back().lex.size());
                    throw SyntaxError("expected operand", tokens[i].pos);
                }
                else throw SyntaxError("expected operator", tokens[i].pos);
                break;
            default: break;
        }

        if (tClass == TokenClass::END) break;

        state = toDo.nextState;
        i += 1;
    }
}