#include <gtest/gtest.h>
#include "PostfixConverter.hpp"

TEST(PostfixConverterTests, EmptyStackOnFirstOperator) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].lex, "4");
    EXPECT_EQ(tokens[1].lex, "2");
    EXPECT_EQ(tokens[2].lex, "+");
}

TEST(PostfixConverterTests, CheckForIncreasedPriority) {
    std::vector<Token> tokens = {
        {Type::INT, "2"},
        {Type::PLUS, "+"},
        {Type::DOUBLE, "3."},
        {Type::MULTIPLY, "*"},
        {Type::INT, "4"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].lex, "2");
    EXPECT_EQ(tokens[1].lex, "3.");
    EXPECT_EQ(tokens[2].lex, "4");
    EXPECT_EQ(tokens[3].lex, "*");
    EXPECT_EQ(tokens[4].lex, "+");
}

TEST(PostfixConverterTests, CheckForReductionPriority) {
    std::vector<Token> tokens = {
        {Type::INT, "2"},
        {Type::MULTIPLY, "*"},
        {Type::DOUBLE, "3."},
        {Type::PLUS, "+"},
        {Type::INT, "4"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].lex, "2");
    EXPECT_EQ(tokens[1].lex, "3.");
    EXPECT_EQ(tokens[2].lex, "*");
    EXPECT_EQ(tokens[3].lex, "4");
    EXPECT_EQ(tokens[4].lex, "+");
}

TEST(PostfixConverterTests, CheckEqualPriority) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::MINUS, "-"},
        {Type::INT, "2"},
        {Type::MINUS, "-"},
        {Type::INT, "1"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].lex, "4");
    EXPECT_EQ(tokens[1].lex, "2");
    EXPECT_EQ(tokens[2].lex, "-");
    EXPECT_EQ(tokens[3].lex, "1");
    EXPECT_EQ(tokens[4].lex, "-");
}

TEST(PostfixConverterTests, Parenthesis) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::MULTIPLY, "*"},
        {Type::LEFTBRACKET, "("},
        {Type::INT, "2"},
        {Type::MINUS, "-"},
        {Type::INT, "1"},
        {Type::RIGHTBRACKET, ")"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].lex, "4");
    EXPECT_EQ(tokens[1].lex, "2");
    EXPECT_EQ(tokens[2].lex, "1");
    EXPECT_EQ(tokens[3].lex, "-");
    EXPECT_EQ(tokens[4].lex, "*");
}

TEST(PostfixConverterTests, GroupsOfParenthesis) {
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "("},
        {Type::INT, "4"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
        {Type::RIGHTBRACKET, ")"},
        {Type::MULTIPLY, "*"},
        {Type::LEFTBRACKET, "("},
        {Type::INT, "10"},
        {Type::MINUS, "-"},
        {Type::INT, "5"},
        {Type::RIGHTBRACKET, ")"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 7);

    EXPECT_EQ(tokens[0].lex, "4");
    EXPECT_EQ(tokens[1].lex, "2");
    EXPECT_EQ(tokens[2].lex, "+");
    EXPECT_EQ(tokens[3].lex, "10");
    EXPECT_EQ(tokens[4].lex, "5");
    EXPECT_EQ(tokens[5].lex, "-");
    EXPECT_EQ(tokens[6].lex, "*");
}

TEST(PostfixConverterTests, NestedBrackets) {
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "("},
        {Type::LEFTBRACKET, "("},
        {Type::INT, "4"},
        {Type::PLUS, "+"},
        {Type::INT, "2"},
        {Type::RIGHTBRACKET, ")"},
        {Type::RIGHTBRACKET, ")"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].lex, "4");
    EXPECT_EQ(tokens[1].lex, "2");
    EXPECT_EQ(tokens[2].lex, "+");
}

TEST(PostfixConverterTests, OneOperand) {
    std::vector<Token> tokens = {
        {Type::INT, "42"}
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 1);

    EXPECT_EQ(tokens[0].lex, "42");
}

TEST(PostfixConverterTests, PowTest) {
    std::vector<Token> tokens = {
        {Type::INT, "2"},
        {Type::POW, "^"},
        {Type::INT, "3"},
        {Type::POW, "^"},
        {Type::INT, "2"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].lex, "2");
    EXPECT_EQ(tokens[1].lex, "3");
    EXPECT_EQ(tokens[2].lex, "2");
    EXPECT_EQ(tokens[3].lex, "^");
    EXPECT_EQ(tokens[4].lex, "^");
}

TEST(PostfixConverterTests, PowTest2) { //дописать
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "("},
        {Type::INT, "2"},
        {Type::POW, "^"},
        {Type::INT, "3"},
        {Type::RIGHTBRACKET, ")"},
        {Type::POW, "^"},
        {Type::INT, "2"},
    };

    tokens = PostfixConverter::convert(tokens);
    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].lex, "2");
    EXPECT_EQ(tokens[1].lex, "3");
    EXPECT_EQ(tokens[2].lex, "^");
    EXPECT_EQ(tokens[3].lex, "2");
    EXPECT_EQ(tokens[4].lex, "^");
}

TEST(PostfixConverterTests, ErrorPosTest1) {
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "(", 0},
        {Type::INT, "2", 1},
        {Type::POW, "^", 2},
        {Type::INT, "3", 3},
    };

    try {
        PostfixConverter::convert(tokens);
    } catch (const PostfixError& e) {
        EXPECT_EQ(e.position(), 0);
    }
}

TEST(PostfixConverterTests, ErrorPosTest2) {
    std::vector<Token> tokens = {
        {Type::INT, "2", 0},
        {Type::RIGHTBRACKET, ")", 1},
    };

    try {
        PostfixConverter::convert(tokens);
    } catch (const PostfixError& e) {
        EXPECT_EQ(e.position(), 1);
    }
}