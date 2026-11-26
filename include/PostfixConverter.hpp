#pragma once

#include <vector>
#include "Token.hpp"
#include "TranslatorError.hpp"

class PostfixConverter {
    public:
    static std::vector<Token> convert(const std::vector<Token>& tokens);
};