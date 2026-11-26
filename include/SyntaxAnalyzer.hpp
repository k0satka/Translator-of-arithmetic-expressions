#pragma once

#include <vector>
#include <stack>
#include <stdexcept>
#include "Token.hpp"
#include "TranslatorError.hpp"

class SyntaxAnalyzer {
    public:
    static void analyze(const std::vector<Token>& tokens);
};