#include <gtest/gtest.h>
#include "Translator.hpp"

struct ExpressionCase {
    std::string expression;
    double expected;
};

class PipelineTests : public ::testing::TestWithParam<ExpressionCase> {};

TEST_P(PipelineTests, CorrectResult) {
    const ExpressionCase& testCase = GetParam();

    EXPECT_DOUBLE_EQ(Translator::translate(testCase.expression), testCase.expected);
}

INSTANTIATE_TEST_SUITE_P(
    ArithmeticExpressions,
    PipelineTests,
    ::testing::Values(
        ExpressionCase{"42", 42.0},
        ExpressionCase{"2+3", 5.0},
        ExpressionCase{"2+3*4", 14.0},
        ExpressionCase{"(2+3)*4", 20.0},
        ExpressionCase{"10-3-2", 5.0},
        ExpressionCase{"24/4/2", 3.0},
        ExpressionCase{"2*(3+(4*5))", 46.0},
        ExpressionCase{"(2+3)*(4-1)", 15.0},
        ExpressionCase{"1.5+2.25", 3.75},
        ExpressionCase{".5*4", 2.0},
        ExpressionCase{"12.+3", 15.0},
        ExpressionCase{"5/2", 2.5},
        ExpressionCase{"2-4", -2.0},
        ExpressionCase{"2 + ( 3 * 4 )", 14.0},
        ExpressionCase{"0.1+0.2", 0.3},
        ExpressionCase{"2^3", 8.0},
        ExpressionCase{"2^3^2", 512.0},
        ExpressionCase{"(2^3)^2", 64.0},
        ExpressionCase{"2*3^2", 18.0},
        ExpressionCase{"2^3*2", 16.0},
        ExpressionCase{"4^0.5", 2.0},
        ExpressionCase{"5^0", 1.0},
        ExpressionCase{"2^1+3", 5.0}
    )
);

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