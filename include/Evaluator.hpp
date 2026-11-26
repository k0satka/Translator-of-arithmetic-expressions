#pragma once

#include <vector>
#include <stack>
#include <stdexcept>
#include <cmath>
#include "Token.hpp"
#include "TranslatorError.hpp"

class Evaluator{
    public:
    static double evaluate(const std::vector<Token>& tokens);
};