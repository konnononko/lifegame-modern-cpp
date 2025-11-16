#include <gtest/gtest.h>

TEST(DummyTest, Fail) {
    EXPECT_TRUE(false);
}

TEST(DummyTest, Success) {
    EXPECT_TRUE(true);
}
