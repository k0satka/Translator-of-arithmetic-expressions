#include <gtest/gtest.h>
#include "Evaluator.hpp"

TEST(EvaluatorTests, OneToken) {
    std::vector<Token> tokens = {
        {Type::INT, "42"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 42.0);
}

TEST(EvaluatorTests, Plus) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::INT, "2"},
        {Type::PLUS, "+"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 6.0);
}

TEST(EvaluatorTests, Minus) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::INT, "2"},
        {Type::MINUS, "-"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 2.0);
}

TEST(EvaluatorTests, Multipy) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::INT, "2"},
        {Type::MULTIPLY, "*"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 8.0);
}

TEST(EvaluatorTests, Divide) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::INT, "2"},
        {Type::DIVIDE, "/"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 2.0);
}

TEST(EvaluatorTests, Priority) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::INT, "2"},
        {Type::INT, "3"},
        {Type::MULTIPLY, "*"},
        {Type::PLUS, "+"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 10.0);
}

TEST(EvaluatorTests, Priority2) {
    std::vector<Token> tokens = {
        {Type::INT, "10"},
        {Type::INT, "5"},
        {Type::MINUS, "-"},
        {Type::INT, "2"},
        {Type::DIVIDE, "/"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 2.5);
}

TEST(EvaluatorTests, Negative) {
    std::vector<Token> tokens = {
        {Type::INT, "0"},
        {Type::INT, "4"},
        {Type::MINUS, "-"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, -4.0);
}

TEST(EvaluatorTests, DoubleOperands) {
    std::vector<Token> tokens = {
        {Type::DOUBLE, "2.5"},
        {Type::DOUBLE, "1.5"},
        {Type::PLUS, "+"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 4.0);
}

TEST(EvaluatorTests, FractionalDivision) {
    std::vector<Token> tokens = {
        {Type::INT, "5"},
        {Type::INT, "2"},
        {Type::DIVIDE, "/"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 2.5);
}

TEST(EvaluatorTests, SmallDivisor) {
    std::vector<Token> tokens = {
        {Type::INT, "1"},
        {Type::DOUBLE, "1e-16"},
        {Type::DIVIDE, "/"},
    };

    double res = Evaluator::evaluate(tokens);

    EXPECT_DOUBLE_EQ(res, 1e16);
}

TEST(EvaluatorTests, DivisionByZero) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::INT, "0"},
        {Type::DIVIDE, "/"},
    };

    EXPECT_THROW(Evaluator::evaluate(tokens), std::runtime_error);
}

TEST(EvaluatorTests, OneOperand) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::PLUS, "+"},
    };

    EXPECT_THROW(Evaluator::evaluate(tokens), std::runtime_error);
}

TEST(EvaluatorTests, WithoutOperator) {
    std::vector<Token> tokens = {
        {Type::INT, "4"},
        {Type::INT, "2"},
    };

    EXPECT_THROW(Evaluator::evaluate(tokens), std::runtime_error);
}

TEST(EvaluatorTests, InvalidToken) {
    std::vector<Token> tokens = {
        {Type::LEFTBRACKET, "("},
    };

    EXPECT_THROW(Evaluator::evaluate(tokens), std::runtime_error);
}

TEST(EvaluatorTests, EmptyInput) {
    std::vector<Token> tokens = { };

    EXPECT_THROW(Evaluator::evaluate(tokens), std::runtime_error);
}

TEST(EvaluatorTests, ErrorPosTest1) {
    std::vector<Token> tokens = { 
        {Type::INT, "5", 0},
        {Type::INT, "0", 2},
        {Type::DIVIDE, "/", 1},
    };

    try {
        Evaluator::evaluate(tokens);
    } catch (const EvaluatorError& e) {
        EXPECT_EQ(e.position(), 1);
    }
}

TEST(EvaluatorTests, ErrorPosTest2) {
    std::vector<Token> tokens = { 
        {Type::INT, "5", 0},
        {Type::INT, "1", 3},
        {Type::INT, "1", 5},
        {Type::MINUS, "-", 4},
        {Type::DIVIDE, "/", 1},
    };

    try {
        Evaluator::evaluate(tokens);
    } catch (const EvaluatorError& e) {
        EXPECT_EQ(e.position(), 1);
    }
}