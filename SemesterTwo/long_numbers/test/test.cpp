#include <gtest/gtest.h>

#include "long_number.hpp"


TEST(LongNumberTest, ComparisonOperators) {
    ussr::LongNumber a("100");
    ussr::LongNumber b("100");
    ussr::LongNumber c("900");
    ussr::LongNumber d("-100");


    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a != b);


    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(d < a);
    EXPECT_FALSE(a < b);
}
TEST(LongNumberTest, ArithmeticOperations) {
    ussr::LongNumber a("100");
    ussr::LongNumber b("900");
    ussr::LongNumber c("-100");
    ussr::LongNumber null;


    EXPECT_EQ(a + b, ussr::LongNumber("1000"));
    EXPECT_EQ(a + c, ussr::LongNumber("0"));
    EXPECT_EQ(a + null, a);


    EXPECT_EQ(b - a, ussr::LongNumber("800"));
    EXPECT_EQ(a - b, ussr::LongNumber("-800"));
    EXPECT_EQ(null - a, ussr::LongNumber("-100"));


    EXPECT_EQ(a * b, ussr::LongNumber("90000"));
    EXPECT_EQ(a * c, ussr::LongNumber("-10000"));
    EXPECT_EQ(a * null, null);

   
    EXPECT_EQ(-a, ussr::LongNumber("-100"));
    EXPECT_EQ(-null, null);
}
TEST(LongNumberTest, DivisionAndModulo) {
    ussr::LongNumber a("100");
    ussr::LongNumber b("11");
    ussr::LongNumber c("-3");

    
    EXPECT_EQ(a / b, ussr::LongNumber("9"));
    EXPECT_EQ(b / c, ussr::LongNumber("-3"));
    EXPECT_EQ(ussr::LongNumber("-19602") / ussr::LongNumber("198") / ussr::LongNumber("-1"), ussr::LongNumber("99"));

 
    EXPECT_EQ(a % b, ussr::LongNumber("1"));
    EXPECT_EQ(b % c, ussr::LongNumber("2"));
}

int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
