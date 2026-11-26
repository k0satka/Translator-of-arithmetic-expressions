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
        {Type::LEFTBRACKET, "(", 0},
        {Type::RIGHTBRACKET, ")", 1},
    };

    try {
        SyntaxAnalyzer::analyze(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_EQ(e.position(), 1);
    }   
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

TEST(SyntaxAnalyzerTest, ErrorPosTest1) {
    std::vector<Token> tokens = { 
        {Type::INT, "1", 0},
        {Type::PLUS, "+", 1},
        {Type::MULTIPLY, "*", 2},
        {Type::DOUBLE, ".4", 3},
    };

    try {
        SyntaxAnalyzer::analyze(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_EQ(e.position(), 2);
    }
}

TEST(SyntaxAnalyzerTest, ErrorPosTest2) {
    std::vector<Token> tokens = { 
        {Type::INT, "2", 0},
        {Type::LEFTBRACKET, "(", 1},
        {Type::INT, "3", 2},
        {Type::PLUS, "+", 3},
        {Type::DOUBLE, ".4", 4},
        {Type::RIGHTBRACKET, ")", 5},
    };

    try {
        SyntaxAnalyzer::analyze(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_EQ(e.position(), 1);
    }
}

TEST(SyntaxAnalyzerTest, ErrorPosTest3) {
    std::vector<Token> tokens = { 
        {Type::INT, "2", 0},
        {Type::PLUS, "+", 1},
        {Type::INT, "3", 2},
        {Type::RIGHTBRACKET, ")", 3},
    };

    try {
        SyntaxAnalyzer::analyze(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_EQ(e.position(), 3);
    }
}

TEST(SyntaxAnalyzerTest, ErrorPosTest4) {
    std::vector<Token> tokens = { 
        {Type::LEFTBRACKET, "(", 0},
        {Type::INT, "2", 1},
        {Type::PLUS, "+", 2},
        {Type::INT, "3", 3},
    };

    try {
        SyntaxAnalyzer::analyze(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_EQ(e.position(), 0);
    }
}

TEST(SyntaxAnalyzerTest, ErrorPosTest5) {
    std::vector<Token> tokens = { 
        {Type::INT, "1", 0},
        {Type::PLUS, "+", 1},
    };

    try {
        SyntaxAnalyzer::analyze(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_EQ(e.position(), 2);
    }
}