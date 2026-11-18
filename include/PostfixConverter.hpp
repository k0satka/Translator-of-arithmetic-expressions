#pragma once

#include <vector>
#include <stack>
#include <stdexcept>
#include "Token.hpp"

class PostfixConverter {
    public:
    static std::vector<Token> convert(const std::vector<Token>& tokens);
};