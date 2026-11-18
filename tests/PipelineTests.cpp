#include <gtest/gtest.h>
#include "Translator.hpp"

TEST(PipelineTests, SingleNumber) {
    EXPECT_DOUBLE_EQ(Translator::translate("42"), 42.0);
}

TEST(PipelineTests, Addition) {
    EXPECT_DOUBLE_EQ(Translator::translate("2+3"), 5.0);
}

TEST(PipelineTests, OperatorPriority) {
    EXPECT_DOUBLE_EQ(Translator::translate("2+3*4"), 14.0);
}

TEST(PipelineTests, ParenthesesPriority) {
    EXPECT_DOUBLE_EQ(Translator::translate("(2+3)*4"), 20.0);
}

TEST(PipelineTests, LeftAssociativity) {
    EXPECT_DOUBLE_EQ(Translator::translate("10-3-2"), 5.0);
}

TEST(PipelineTests, DivisionAssociativity) {
    EXPECT_DOUBLE_EQ(Translator::translate("24/4/2"), 3.0);
}

TEST(PipelineTests, NestedBrackets) {
    EXPECT_DOUBLE_EQ(Translator::translate("2*(3+(4*5))"), 46.0);
}

TEST(PipelineTests, MultipleBrackets) {
    EXPECT_DOUBLE_EQ(Translator::translate("(2+3)*(4-1)"), 15.0);
}

TEST(PipelineTests, DoubleNumbers) {
    EXPECT_DOUBLE_EQ(Translator::translate("1.5+2.25"), 3.75);
}

TEST(PipelineTests, LeadingDot) {
    EXPECT_DOUBLE_EQ(Translator::translate(".5*4"), 2.0);
}

TEST(PipelineTests, TrailingDot) {
    EXPECT_DOUBLE_EQ(Translator::translate("12.+3"), 15.0);
}

TEST(PipelineTests, FractionalDivision) {
    EXPECT_DOUBLE_EQ(Translator::translate("5/2"), 2.5);
}

TEST(PipelineTests, NegativeResult) {
    EXPECT_DOUBLE_EQ(Translator::translate("2-4"), -2.0);
}

TEST(PipelineTests, Whitespace) {
    EXPECT_DOUBLE_EQ(Translator::translate("2 + ( 3 * 4 )"), 14.0);
}

TEST(PipelineTests, FloatingPointPrecision) {
    EXPECT_DOUBLE_EQ(Translator::translate("0.1+0.2"), 0.3);
}

TEST(PipelineTests, DivisionByZero) {
    EXPECT_THROW(Translator::translate("5/0"), std::runtime_error);
}

class InvalidExpressionTest : public testing::TestWithParam<std::string> {};

TEST_P(InvalidExpressionTest, ThrowsException) {
    EXPECT_THROW(Translator::translate(GetParam()), std::runtime_error);
}

INSTANTIATE_TEST_SUITE_P(
    LexicalErrors,
    InvalidExpressionTest,
    testing::Values(
        "2@3",
        "."
    )
);

INSTANTIATE_TEST_SUITE_P(
    SyntaxErrors,
    InvalidExpressionTest,
    testing::Values(
        "1+*2",
        "1++2",
        "(1+2",
        "1+2)",
        "1 2",
        "12.3.4",
        "2(3+4)",
        "-5+2",
        "()",
        ""
    )
);

INSTANTIATE_TEST_SUITE_P(
    EvaluationErrors,
    InvalidExpressionTest,
    testing::Values(
        "5/0",
        "5/(3-3)"
    )
);