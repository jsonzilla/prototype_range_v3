#include "gtest/gtest.h"

TEST(example, demo)
{
  EXPECT_FALSE(2 == 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}