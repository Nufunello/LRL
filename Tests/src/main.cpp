#include <gtest/gtest.h>

TEST(HelloWorld, Positive)
{
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloWorld, Negative)
{
  EXPECT_EQ(7 * 6 + 1, 42);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}