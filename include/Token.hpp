#pragma once

#include <string>
#include "TokenType.hpp"

struct Token {
    Type type;
    std::string lex;
};