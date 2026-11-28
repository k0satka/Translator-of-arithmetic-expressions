#include "Token.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "PostfixConverter.hpp"
#include "Evaluator.hpp"

#include "Translator.hpp"

double Translator::translate(const std::string& str) {
    std::vector<Token> tokens = LexicalAnalyzer::analyze(str);
    SyntaxAnalyzer::analyze(tokens);
    tokens = PostfixConverter::convert(tokens);
    return Evaluator::evaluate(tokens, variables);
}