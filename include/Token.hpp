#pragma once

#include <string>
#include "TokenType.hpp"

struct Token {
    Type type;
    std::string lex;
    size_t pos = std::string::npos; //по умолчанию -1 чтобы не переписывать тесты
};