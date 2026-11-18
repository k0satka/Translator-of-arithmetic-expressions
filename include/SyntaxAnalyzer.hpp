#pragma once

#include <string>
#include <vector>
#include <stack>
#include <stdexcept>
#include "Token.hpp"

class SyntaxAnalyzer {
    public:
    static void analyze(const std::vector<Token>& tokens);
};