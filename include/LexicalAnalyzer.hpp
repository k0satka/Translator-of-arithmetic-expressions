#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include "Token.hpp"

//принимает предложение и возвращает набор токенов или ошибку через exc
class LexicalAnalyzer {
    public:
    static std::vector<Token> analyze(const std::string& str);
};