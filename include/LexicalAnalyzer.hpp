#pragma once

#include <string>
#include <vector>
#include "Token.hpp"
#include "TranslatorError.hpp"

//принимает предложение и возвращает набор токенов или ошибку через exc
class LexicalAnalyzer {
    public:
    static std::vector<Token> analyze(const std::string& str);
};