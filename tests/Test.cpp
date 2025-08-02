#include <fuse.h>

#include <gtest/gtest.h>

TEST(ExampleTest, BasicAssertions) { EXPECT_EQ(2, fuse::add(1, 1)); }
