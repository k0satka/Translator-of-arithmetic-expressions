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