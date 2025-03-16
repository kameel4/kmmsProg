#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "long_number.hpp"

using namespace biv;

// arithmetic operators

TEST(LongNumber, test_summation) {
    LongNumber a = "1230";
    LongNumber b = "456";
    LongNumber c = "1686";
    ASSERT_EQ(c, a + b);
}

TEST(LongNumber, test_subtraction) {
    LongNumber a = "456";
    LongNumber b = "123";
    LongNumber c = "333";
    ASSERT_EQ(c, a - b);
}

TEST(LongNumber, test_multiplication) {
    LongNumber a = "123";
    LongNumber b = "456";
    LongNumber c = "56088";
    ASSERT_EQ(c, a * b);
}

TEST(LongNumber, test_division) {
    LongNumber a = "169";
    LongNumber b = "13";
    LongNumber c = "13";
    ASSERT_EQ(c, a / b);
}

TEST(LongNumber, test_modulo) {
    LongNumber a = "136";
    LongNumber b = "13";
    LongNumber c = "6";
    ASSERT_EQ(c, a % b);
}

//comparison operators
TEST(LongNumber, Equality) {
    LongNumber a = "1234";
    LongNumber b = "1234";
    ASSERT_EQ(a, b);
}

TEST(LongNumber, Inequality) {
    LongNumber a = "1234";
    LongNumber b = "1235";
    ASSERT_NE(a, b);
}

TEST(LongNumber, LessThan) {
    LongNumber a = "1234";
    LongNumber b = "1235";
    ASSERT_LT(a, b);
}

TEST(LongNumber, GreaterThan) {
    LongNumber a = "1235";
    LongNumber b = "1234";
    ASSERT_GT(a, b);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}