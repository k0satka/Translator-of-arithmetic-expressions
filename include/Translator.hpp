#pragma once

#include <string>
#include "Token.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "PostfixConverter.hpp"
#include "Evaluator.hpp"

class Translator {
private:
    //быстрый словарь для переменных на базе хеш таблицы
    std::unordered_map<std::string, double> variables;
public:
    double translate(const std::string& str);
};
