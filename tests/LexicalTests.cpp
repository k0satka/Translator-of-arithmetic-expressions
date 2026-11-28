#include <gtest/gtest.h>
#include "LexicalAnalyzer.hpp"

TEST(LexicalAnalyzerTest, IntegerNumber) {
    auto tokens = LexicalAnalyzer::analyze("123");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::INT);
    EXPECT_EQ(tokens[0].lex, "123");
}

TEST(LexicalAnalyzerTest, DoubleNumber) {
    auto tokens = LexicalAnalyzer::analyze("4.2");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::DOUBLE);
    EXPECT_EQ(tokens[0].lex, "4.2");
}

TEST(LexicalAnalyzerTest, LeadingDot) {
    auto tokens = LexicalAnalyzer::analyze(".2");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::DOUBLE);
    EXPECT_EQ(tokens[0].lex, ".2");
}

TEST(LexicalAnalyzerTest, TrailingDot) {
    auto tokens = LexicalAnalyzer::analyze("4.");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::DOUBLE);
    EXPECT_EQ(tokens[0].lex, "4.");
}

TEST(LexicalAnalyzerTest, BinaryOperators) {
    auto tokens = LexicalAnalyzer::analyze("1*2.  +3");

    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].type, Type::INT);
    EXPECT_EQ(tokens[0].lex, "1");
    EXPECT_EQ(tokens[1].type, Type::MULTIPLY);
    EXPECT_EQ(tokens[1].lex, "*");
    EXPECT_EQ(tokens[2].type, Type::DOUBLE);
    EXPECT_EQ(tokens[2].lex, "2.");
    EXPECT_EQ(tokens[3].type, Type::PLUS);
    EXPECT_EQ(tokens[3].lex, "+");
    EXPECT_EQ(tokens[4].type, Type::INT);
    EXPECT_EQ(tokens[4].lex, "3");
}

TEST(LexicalAnalyzerTest, Brackets) {
    auto tokens = LexicalAnalyzer::analyze("(1..0 )*2");

    ASSERT_EQ(tokens.size(), 6);

    EXPECT_EQ(tokens[0].type, Type::LEFTBRACKET);
    EXPECT_EQ(tokens[0].lex, "(");
    EXPECT_EQ(tokens[1].type, Type::DOUBLE);
    EXPECT_EQ(tokens[1].lex, "1.");
    EXPECT_EQ(tokens[2].type, Type::DOUBLE);
    EXPECT_EQ(tokens[2].lex, ".0");
    EXPECT_EQ(tokens[3].type, Type::RIGHTBRACKET);
    EXPECT_EQ(tokens[3].lex, ")");
    EXPECT_EQ(tokens[4].type, Type::MULTIPLY);
    EXPECT_EQ(tokens[4].lex, "*");
    EXPECT_EQ(tokens[5].type, Type::INT);
    EXPECT_EQ(tokens[5].lex, "2");
}

TEST(LexicalAnalyzerTest, Spaces) {
    auto tokens = LexicalAnalyzer::analyze("  *.2 ");

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, Type::MULTIPLY);
    EXPECT_EQ(tokens[0].lex, "*");
    EXPECT_EQ(tokens[1].type, Type::DOUBLE);
    EXPECT_EQ(tokens[1].lex, ".2");
}

TEST(LexicalAnalyzerTest, InvalidCharacter) {
    EXPECT_THROW(LexicalAnalyzer::analyze("1@2"), std::runtime_error);
}

TEST(LexicalAnalyzerTest, SingleDot) {
    EXPECT_THROW(LexicalAnalyzer::analyze("  . "), std::runtime_error);
}

TEST(LexicalAnalyzerTest, EmptyInput) {
    auto tokens = LexicalAnalyzer::analyze("");

    EXPECT_TRUE(tokens.empty());
}

TEST(LexicalTests, TokenPositions) {
    auto tokens = LexicalAnalyzer::analyze("12 + (3.5)");

    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].pos, 0);
    EXPECT_EQ(tokens[1].pos, 3);
    EXPECT_EQ(tokens[2].pos, 5);
    EXPECT_EQ(tokens[3].pos, 6);
    EXPECT_EQ(tokens[4].pos, 9);
}

TEST(LexicalTests, TokenPositions2) {
    auto tokens = LexicalAnalyzer::analyze("(.5+2)");

    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].pos, 0);
    EXPECT_EQ(tokens[1].pos, 1);
    EXPECT_EQ(tokens[2].pos, 3);
    EXPECT_EQ(tokens[3].pos, 4);
    EXPECT_EQ(tokens[4].pos, 5);
}

TEST(LexicalTests, TokenPositions3) {
    auto tokens = LexicalAnalyzer::analyze("2^3");

    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].pos, 0);
    EXPECT_EQ(tokens[1].pos, 1);
    EXPECT_EQ(tokens[2].pos, 2);
}

TEST(LexicalTests, InvalidCharacterPosition) {
    try {
        LexicalAnalyzer::analyze("12@3");
    }
    catch (const LexicalError& e) {
        EXPECT_EQ(e.position(), 2);
        EXPECT_EQ(e.stage(), "LexicalError");
    }
}

TEST(LexicalTests, Dot) {
    try {
        LexicalAnalyzer::analyze(".");
    }
    catch (const LexicalError& e) {
        EXPECT_EQ(e.position(), 0);
        EXPECT_EQ(e.stage(), "LexicalError");
    }
}

TEST(LexicalTests, Dot2) {
    try {
        LexicalAnalyzer::analyze(".+2");
    }
    catch (const LexicalError& e) {
        EXPECT_EQ(e.position(), 0);
        EXPECT_EQ(e.stage(), "LexicalError");
    }
}

TEST(LexicalTests, InvalidSimbol) {
    try {
        LexicalAnalyzer::analyze("1+#");
    }
    catch (const LexicalError& e) {
        EXPECT_EQ(e.position(), 2);
        EXPECT_EQ(e.stage(), "LexicalError");
    }
}

TEST(LexicalTests, Dot3) {
    try {
        LexicalAnalyzer::analyze(". 5");
    }
    catch (const LexicalError& e) {
        EXPECT_EQ(e.position(), 0);
        EXPECT_EQ(e.stage(), "LexicalError");
    }
}

TEST(LexicalTests, Dot4) {
    try {
        LexicalAnalyzer::analyze(".#");
    }
    catch (const LexicalError& e) {
        EXPECT_EQ(e.position(), 1);
        EXPECT_EQ(e.stage(), "LexicalError");
    }
}

TEST(LexicalAnalyzerTest, Identifier1) {
    auto tokens = LexicalAnalyzer::analyze("x");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::IDENTIFIER);
    EXPECT_EQ(tokens[0].lex, "x");
    EXPECT_EQ(tokens[0].pos, 0);
}

TEST(LexicalAnalyzerTest, Identifier2) {
    auto tokens = LexicalAnalyzer::analyze("abcd");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::IDENTIFIER);
    EXPECT_EQ(tokens[0].lex, "abcd");
    EXPECT_EQ(tokens[0].pos, 0);
}

TEST(LexicalAnalyzerTest, Identifier3) {
    auto tokens = LexicalAnalyzer::analyze("ab12");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::IDENTIFIER);
    EXPECT_EQ(tokens[0].lex, "ab12");
    EXPECT_EQ(tokens[0].pos, 0);
}

TEST(LexicalAnalyzerTest, Identifier4) {
    auto tokens = LexicalAnalyzer::analyze("_ab12");

    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].type, Type::IDENTIFIER);
    EXPECT_EQ(tokens[0].lex, "_ab12");
    EXPECT_EQ(tokens[0].pos, 0);
}

TEST(LexicalAnalyzerTest, Identifier5) {
    auto tokens = LexicalAnalyzer::analyze("x+42");

    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].type, Type::IDENTIFIER);
    EXPECT_EQ(tokens[0].lex, "x");
    EXPECT_EQ(tokens[0].pos, 0);
    EXPECT_EQ(tokens[1].type, Type::PLUS);
    EXPECT_EQ(tokens[1].lex, "+");
    EXPECT_EQ(tokens[1].pos, 1);
    EXPECT_EQ(tokens[2].type, Type::INT);
    EXPECT_EQ(tokens[2].lex, "42");
    EXPECT_EQ(tokens[2].pos, 2);
}

TEST(LexicalAnalyzerTest, IdentifierAndAssign) {
    auto tokens = LexicalAnalyzer::analyze("x=42");

    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].type, Type::IDENTIFIER);
    EXPECT_EQ(tokens[0].lex, "x");
    EXPECT_EQ(tokens[0].pos, 0);
    EXPECT_EQ(tokens[1].type, Type::ASSIGN);
    EXPECT_EQ(tokens[1].lex, "=");
    EXPECT_EQ(tokens[1].pos, 1);
    EXPECT_EQ(tokens[2].type, Type::INT);
    EXPECT_EQ(tokens[2].lex, "42");
    EXPECT_EQ(tokens[2].pos, 2);
}