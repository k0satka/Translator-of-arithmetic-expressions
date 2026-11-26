#include <gtest/gtest.h>
#include "TranslatorError.hpp"

TEST(TranslatorErrorTests, LexicalErrorType) {
    EXPECT_THROW(throw LexicalError("invalid character", 3), LexicalError);
}

TEST(TranslatorErrorTests, LexicalErrorTest) {
    LexicalError error("invalid character", 3);

    EXPECT_EQ(error.stage(), "LexicalError");
    EXPECT_EQ(error.position(), 3);
    EXPECT_STREQ(error.what(), "invalid character");
}