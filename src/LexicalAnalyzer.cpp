#include "LexicalAnalyzer.hpp"

namespace {
//состояния КА
enum class State { START, INT, DOT, RPART, size }; 

//классификация символов
enum class SymbolClass { DIGIT, DOT, OPERATOR, LEFTBRACKET, RIGHTBRACKET, SPACE, END, INVALID, size };
SymbolClass classify(char a) {
    if (a >= '0' && a <= '9') return SymbolClass::DIGIT;
    else if (a == '.') return SymbolClass::DOT;
    else if (a == '+' || a == '-' || a == '*' || a == '/') return SymbolClass::OPERATOR;
    else if (a == '(') return SymbolClass::LEFTBRACKET;
    else if (a == ')') return SymbolClass::RIGHTBRACKET;
    else if (a == ' ' || a == '\n' || a == '\t') return SymbolClass::SPACE;
    else return SymbolClass::INVALID;
}

//возможные действия
enum class Action { NONE, START_LEXEM, ADD_SIMB, SAVE_INT, SAVE_DOUBLE, SAVE_OPERATOR_BRACKET, SEND_ERROR, size };
//нужна вспомогательная функ потому что теряем информацию о символе разбивая их на типы, не понятно какой тип указывать при сохранении токена действием SAVE_OPERATOR_BRACKET
Type getTokenType(char a){
    switch (a) {
    case '+': return Type::PLUS;
    case '-': return Type::MINUS;
    case '*': return Type::MULTIPLY;
    case '/': return Type::DIVIDE;
    case '(': return Type::LEFTBRACKET;
    case ')': return Type::RIGHTBRACKET;
    default: throw std::invalid_argument("processed only +-*/()");
    }
}

struct Cell {
    State nextState;
    Action action;
    bool consume = true; //нужен для двойной обработки символа, чтобы не выполнять два действия за шаг
};

//таблица с правилами, где по состоянию и символу можно посмотреть следующее состояние и действие
constexpr Cell table[static_cast<size_t>(State::size)][static_cast<size_t>(SymbolClass::size)] = {
    /*START*/{
        { State::INT, Action::START_LEXEM }, //digit
        { State::DOT, Action::START_LEXEM }, //dot
        { State::START, Action::SAVE_OPERATOR_BRACKET }, //operator
        { State::START, Action::SAVE_OPERATOR_BRACKET }, //lBracket
        { State::START, Action::SAVE_OPERATOR_BRACKET }, //rBracket
        { State::START, Action::NONE }, //space
        { State::START, Action::NONE }, //end
        { State::START, Action::SEND_ERROR }, //invalid
    },
    /*INT*/{
        { State::INT, Action::ADD_SIMB }, //digit
        { State::RPART, Action::ADD_SIMB }, //dot
        { State::START, Action::SAVE_INT, false }, //operator. для двойной обработки consume = false
        { State::START, Action::SAVE_INT, false }, //lBracket
        { State::START, Action::SAVE_INT, false }, //rBracket
        { State::START, Action::SAVE_INT }, //space
        { State::START, Action::SAVE_INT }, //end
        { State::START, Action::SEND_ERROR }, //invalid
    },
    /*DOT*/{
        { State::RPART, Action::ADD_SIMB }, //digit
        { State::START, Action::SEND_ERROR }, //dot
        { State::START, Action::SEND_ERROR }, //operator
        { State::START, Action::SEND_ERROR }, //lBracket
        { State::START, Action::SEND_ERROR }, //rBracket
        { State::START, Action::SEND_ERROR }, //space
        { State::START, Action::SEND_ERROR }, //end
        { State::START, Action::SEND_ERROR }, //invalid
    },
    /*RPART*/{
        { State::RPART, Action::ADD_SIMB }, //digit
        { State::START, Action::SAVE_DOUBLE, false }, //dot
        { State::START, Action::SAVE_DOUBLE, false }, //operator
        { State::START, Action::SAVE_DOUBLE, false }, //lBracket
        { State::START, Action::SAVE_DOUBLE, false }, //rBracket
        { State::START, Action::SAVE_DOUBLE }, //space
        { State::START, Action::SAVE_DOUBLE }, //end
        { State::START, Action::SEND_ERROR }, //invalid
    }
};
}


//конечный автомат
std::vector<Token> LexicalAnalyzer::analyze(const std::string& str) {
    
    std::vector<Token> res; //результат
    State state = State::START; //начальное состояние
    std::string lexem; //лексема для токена
    SymbolClass sClass; //тип символа
    
    size_t len = str.size();
    size_t i = 0; //индекс читаемого символа
    char ch; //читаемый символ

    while (i <= len) {
        if (i < len) {
            ch = str[i];
            sClass = classify(ch);
        } else sClass = SymbolClass::END;

        Cell toDo = table[static_cast<size_t>(state)][static_cast<size_t>(sClass)];
        
        //выполняем действие
        switch (toDo.action) {
        case Action::NONE: break;
        case Action::START_LEXEM: lexem = std::string(1, ch); break;
        case Action::ADD_SIMB: lexem.push_back(ch); break;
        case Action::SAVE_INT: res.emplace_back(Type::INT, lexem); break;
        case Action::SAVE_DOUBLE: res.emplace_back(Type::DOUBLE, lexem); break;
        case Action::SAVE_OPERATOR_BRACKET: res.emplace_back(getTokenType(ch), std::string(1, ch)); break;
        case Action::SEND_ERROR: throw std::runtime_error("lexical analysis error");
        default: break;
        }

        //выходим 
        if (sClass == SymbolClass::END) break;

        state = toDo.nextState;
        if (toDo.consume) i += 1;
    }

    return res;
}