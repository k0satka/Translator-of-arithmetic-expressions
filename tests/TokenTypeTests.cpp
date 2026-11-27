#include <gtest/gtest.h>
#include "TokenType.hpp"

TEST(TokenTypeTests, OperatorProperties) {
    auto plus = getOperatorInfo(Type::PLUS);
    auto multiply = getOperatorInfo(Type::MULTIPLY);
    auto pow = getOperatorInfo(Type::POW);

    EXPECT_EQ(plus.priority, 1);
    EXPECT_EQ(plus.arity, 2);
    EXPECT_EQ(plus.associativity, Associativity::LEFT);

    EXPECT_EQ(multiply.priority, 2);
    EXPECT_EQ(multiply.arity, 2);
    EXPECT_EQ(multiply.associativity, Associativity::LEFT);

    EXPECT_EQ(pow.priority, 4);
    EXPECT_EQ(pow.arity, 2);
    EXPECT_EQ(pow.associativity, Associativity::RIGHT);
}