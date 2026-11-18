#pragma once

#include <string>
#include "Token.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "PostfixConverter.hpp"
#include "Evaluator.hpp"

class Translator {
public:
    static double translate(const std::string& str);
};
