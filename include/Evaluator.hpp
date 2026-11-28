#pragma once

#include <vector>
#include "Token.hpp"
#include "TranslatorError.hpp"

class Evaluator{
    public:
    static double evaluate(const std::vector<Token>& tokens, std::unordered_map<std::string, double>& variables);
};