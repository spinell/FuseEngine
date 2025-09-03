#include <FuseCore/utils/EnumFlags.h>

#include <gtest/gtest.h>

namespace {

constexpr int BITS(int shift) { return 1 << shift; }

enum class Option : std::uint8_t {
    None   = 0,
    Value1 = BITS(0),
    Value2 = BITS(1),
    Value3 = BITS(2),
    Value4 = BITS(3),
    Value5 = BITS(4),
};

} // namespace

TEST(EnumFlags, ctor_default) {
    const fuse::EnumFlags<Option> optionFlags;
    EXPECT_FALSE(optionFlags.isSet(Option::Value1));
    EXPECT_FALSE(optionFlags.isSet(Option::Value2));
    EXPECT_FALSE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));
}

TEST(EnumFlags, ctor_with_param) {
    const fuse::EnumFlags<Option> optionFlags(Option::Value1, Option::Value2, Option::Value3);
    EXPECT_TRUE(optionFlags.isSet(Option::Value1));
    EXPECT_TRUE(optionFlags.isSet(Option::Value2));
    EXPECT_TRUE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));
}

TEST(EnumFlags, operator_flip) {
    const fuse::EnumFlags<Option> optionFlags(Option::Value1, Option::Value2, Option::Value3);
    const fuse::EnumFlags<Option> optionFlags2 = ~optionFlags;
    EXPECT_FALSE(optionFlags2.isSet(Option::Value1));
    EXPECT_FALSE(optionFlags2.isSet(Option::Value2));
    EXPECT_FALSE(optionFlags2.isSet(Option::Value3));
    EXPECT_TRUE(optionFlags2.isSet(Option::Value4));
    EXPECT_TRUE(optionFlags2.isSet(Option::Value5));
}

TEST(EnumFlags, isSet) {
    const fuse::EnumFlags<Option> optionFlags(Option::Value1, Option::Value2);
    EXPECT_TRUE(optionFlags.isSet(Option::Value1));
    EXPECT_TRUE(optionFlags.isSet(Option::Value2));
    EXPECT_FALSE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));
}

TEST(EnumFlags, isAnySet) {
    const fuse::EnumFlags<Option> optionFlags(Option::Value1, Option::Value2, Option::Value3);
    EXPECT_TRUE(optionFlags.isAnySet(Option::Value1));
    EXPECT_TRUE(optionFlags.isAnySet(Option::Value2));
    EXPECT_TRUE(optionFlags.isAnySet(Option::Value3));
    EXPECT_FALSE(optionFlags.isAnySet(Option::Value4));
    EXPECT_FALSE(optionFlags.isAnySet(Option::Value5));

    // Value1 is set
    // Value2 is set
    EXPECT_TRUE(optionFlags.isAnySet(Option::Value1, Option::Value2));

    // Value1 is set
    // Value5 is not set
    EXPECT_TRUE(optionFlags.isAnySet(Option::Value1, Option::Value5));

    // Value4 is not set
    // Value5 is not set
    EXPECT_FALSE(optionFlags.isAnySet(Option::Value4, Option::Value5));
}

TEST(EnumFlags, set) {
    fuse::EnumFlags<Option> optionFlags;
    EXPECT_FALSE(optionFlags.isSet(Option::Value1));
    EXPECT_FALSE(optionFlags.isSet(Option::Value2));
    EXPECT_FALSE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));

    // set one flag
    optionFlags.set(Option::Value1);
    EXPECT_TRUE(optionFlags.isSet(Option::Value1));
    EXPECT_FALSE(optionFlags.isSet(Option::Value2));
    EXPECT_FALSE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));

    // set multi bits
    optionFlags.set(Option::Value1, Option::Value3, Option::Value5);
    EXPECT_TRUE(optionFlags.isSet(Option::Value1));
    EXPECT_FALSE(optionFlags.isSet(Option::Value2));
    EXPECT_TRUE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_TRUE(optionFlags.isSet(Option::Value5));
}

TEST(EnumFlags, unset) {
    fuse::EnumFlags<Option> optionFlags(Option::Value1, Option::Value2, Option::Value3);
    EXPECT_TRUE(optionFlags.isSet(Option::Value1));
    EXPECT_TRUE(optionFlags.isSet(Option::Value2));
    EXPECT_TRUE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));

    // unset one flag
    optionFlags.unset(Option::Value1);
    EXPECT_FALSE(optionFlags.isSet(Option::Value1));
    EXPECT_TRUE(optionFlags.isSet(Option::Value2));
    EXPECT_TRUE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));

    // unset multiple flag
    optionFlags.unset(Option::Value2, Option::Value3);
    EXPECT_FALSE(optionFlags.isSet(Option::Value1));
    EXPECT_FALSE(optionFlags.isSet(Option::Value2));
    EXPECT_FALSE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));

    // unset flag which are already unset.
    // nothing should change
    optionFlags.unset(Option::Value1,
                      Option::Value2,
                      Option::Value3,
                      Option::Value4,
                      Option::Value5);
    EXPECT_FALSE(optionFlags.isSet(Option::Value1));
    EXPECT_FALSE(optionFlags.isSet(Option::Value2));
    EXPECT_FALSE(optionFlags.isSet(Option::Value3));
    EXPECT_FALSE(optionFlags.isSet(Option::Value4));
    EXPECT_FALSE(optionFlags.isSet(Option::Value5));
}

enum class Option2 : std::uint8_t {
    None   = 0,
    Value1 = BITS(0),
    Value2 = BITS(1),
    Value3 = BITS(2),
    Value4 = BITS(3),
    Value5 = BITS(4),
};
