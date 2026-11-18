#include <gtest/gtest.h>
#include "SyntaxAnalyzer.hpp"

TEST(SyntaxAnalyzerTest, SingleNumber) {
    std::vector<Token> tokens = {
        {Type::INT, "42"},
    };

    EXPECT_NO_THROW(SyntaxAnalyzer::analyze(tokens));    
}

TEST(SyntaxAnalyzerTest, SimpleExpression) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
    };

    EXPECT_NO_THROW(SyntaxAnalyzer::analyze(tokens));    
}

TEST(SyntaxAnalyzerTest, NestedBrackets) { //((1+2)*.3)
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "("},
        {Type::LEFTBRACKET, "("},
        {Type::INT, "1"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
        {Type::RIGHTBRACKET, ")"},
        {Type::MULTIPLY, "*"},
        {Type::DOUBLE, ".3"},
        {Type::RIGHTBRACKET, ")"},
    };

    EXPECT_NO_THROW(SyntaxAnalyzer::analyze(tokens));    
}

TEST(SyntaxAnalyzerTest, TwoOperators) {
    std::vector<Token> tokens = {
        {Type::INT, "1"},
        {Type::PLUS, "+"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
    };

    EXPECT_THROW(SyntaxAnalyzer::analyze(tokens), std::runtime_error);    
}

TEST(SyntaxAnalyzerTest, MissingOperand) {
    std::vector<Token> tokens = {
        {Type::INT, "1"},
        {Type::PLUS, "+"},
    };

    EXPECT_THROW(SyntaxAnalyzer::analyze(tokens), std::runtime_error);    
}

TEST(SyntaxAnalyzerTest, ExtraRightBracket) {
    std::vector<Token> tokens = {
        {Type::INT, "1"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
        {Type::RIGHTBRACKET, ")"},
    };

    EXPECT_THROW(SyntaxAnalyzer::analyze(tokens), std::runtime_error);    
}

TEST(SyntaxAnalyzerTest, MissingRightBracket) {
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "("},
        {Type::INT, "1"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
    };

    EXPECT_THROW(SyntaxAnalyzer::analyze(tokens), std::runtime_error);    
}

TEST(SyntaxAnalyzerTest, EmptyBrackets) {
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "("},
        {Type::RIGHTBRACKET, ")"},
    };

    EXPECT_THROW(SyntaxAnalyzer::analyze(tokens), std::runtime_error);    
}

TEST(SyntaxAnalyzerTest, AdjacentNumbers) {
    std::vector<Token> tokens = {
        {Type::INT, "2"},
        {Type::DOUBLE, ".4"},
    };

    EXPECT_THROW(SyntaxAnalyzer::analyze(tokens), std::runtime_error);    
}

TEST(SyntaxAnalyzerTest, EmptyExpression) {
    std::vector<Token> tokens = { };

    EXPECT_THROW(SyntaxAnalyzer::analyze(tokens), std::runtime_error);  
}