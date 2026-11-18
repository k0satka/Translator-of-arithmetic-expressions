#pragma once

#include <vector>
#include "Token.hpp"

class SyntaxAnalyzer {
    public:
    static void analyze(const std::vector<Token>& tokens);
};