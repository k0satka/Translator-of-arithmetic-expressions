#pragma once

#include <vector>
#include <stack>
#include <stdexcept>
#include "Token.hpp"

class Evaluator{
    public:
    static double evaluate(const std::vector<Token>& tokens);
};