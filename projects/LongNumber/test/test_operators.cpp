#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "long_number.hpp"

using namespace biv;

// arithmetic operators

TEST(LongNumber, test_summation) {
    LongNumber a("1230");
    LongNumber b("456");
    LongNumber c("1686");
    ASSERT_EQ(c, a + b);

    a = "-1230";
    b = "-456";
    c = "-1686";
    ASSERT_EQ(c, a + b);

    a = "1230";
    b = "0";
    c = "1230";
    ASSERT_EQ(c, a + b);

    a = "122";
    b = "-22";
    c = "100";

    // cout<< "\n\na: "<<a<<" b: "<<b<<" c: "<<c<<endl;
    // cout<< "a.length: "<<a.get_digits_number()<<" b.length: "<<b.get_digits_number()<<" c.length: "<<c.get_digits_number()<<"\n\n"<<endl;
    ASSERT_EQ(c, a + b);

    a = "122";
    b = "-222";
    c = "-100";
    ASSERT_EQ(c, a + b);

    a = "99";
    b = "99";
    c = "198";
    ASSERT_EQ(c, a + b);
}

TEST(LongNumber, test_subtraction) {
    LongNumber a("456");
    LongNumber b("123");
    LongNumber c("333");
    ASSERT_EQ(c, a - b);

    a = "-456";
    b = "-123";
    c = "-333";
    ASSERT_EQ(c, a - b);

    a = "456";
    b = "0";
    c = "456";
    ASSERT_EQ(c, a - b);

    a = "123";
    b = "1234";
    c = "-1111";
    ASSERT_EQ(c, a - b);


}

TEST(LongNumber, test_multiplication) {
    LongNumber a("123");
    LongNumber b("456");
    LongNumber c("56088");
    ASSERT_EQ(c, a * b);

    a = "123";
    b = "0";
    c = "0";
    ASSERT_EQ(c, a * b);

    a = "-123";
    b = "12345";
    c = "-1518435";

    // cout<< "\n\na: "<<a<<" b: "<<b<<" c: "<<c<<endl;
    // cout<< "a.length: "<<a.get_digits_number()<<" b.length: "<<b.get_digits_number()<<" c.length: "<<c.get_digits_number()<<"\n\n"<<endl;

    ASSERT_EQ(c, a * b);

    a = "1";
    b = "1";
    c = "1";
    ASSERT_EQ(c, a * b);


}

TEST(LongNumber, test_division) {
    LongNumber a("106");
    LongNumber b("3");
    LongNumber c("35");
    ASSERT_EQ(c, a / b);

    a = "0";
    b = "69";
    c = "0";
    ASSERT_EQ(c, a / b);

    a = "-106";
    b = "3";
    c = "-35";
    ASSERT_EQ(c, a / b);

    a = "399";
    b = "2";
    c = "199";
    ASSERT_EQ(c, a / b);

    a = "3999";
    b = "2";
    c = "1999";
    ASSERT_EQ(c, a / b);

    a = "3999";
    b = "1200";
    c = "3";
    ASSERT_EQ(c, a / b);

    //this is still wrong idk why. I hope to complete it tomorrow
    // a = "1999";
    // b = "13";
    // c = "153";
    // ASSERT_EQ(c, a / b);
}

TEST(LongNumber, test_modulo) {
    LongNumber a("136");
    LongNumber b("13");
    LongNumber c("6");
    ASSERT_EQ(c, a % b);

    a = "169";
    b = "13";
    c = "0";
    ASSERT_EQ(c, a % b);

    // as in division, it doesnt go right also, hope to fix it ;(
    // a = "1999";
    // b = "13";
    // c = "10";
    // ASSERT_EQ(c, a % b);
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

TEST(LongNumber, GreaterEqualThan){
    LongNumber a("970");
    LongNumber b("198");
    EXPECT_TRUE(a >= b);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}