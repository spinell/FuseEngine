#include <FuseCore/utils/EnumUtils.h>

#include <gtest/gtest.h>

#include <array>
#include <type_traits>

TEST(GetEnumName, GetEnumName) {
    using namespace std::literals;
    // unscoped enum
    {
        enum Color : std::uint8_t { kRed, kGreen, kBlue };

        static_assert(fuse::getEnumName<kRed>() == "kRed");
        static_assert(fuse::getEnumName<kGreen>() == "kGreen");
        static_assert(fuse::getEnumName<kBlue>() == "kBlue");
        EXPECT_EQ(fuse::getEnumName<kRed>(), "kRed"sv);
        EXPECT_EQ(fuse::getEnumName<kGreen>(), "kGreen"sv);
        EXPECT_EQ(fuse::getEnumName<kBlue>(), "kBlue"sv);

        static_assert(fuse::getEnumName<Color::kRed>() == "kRed");
        static_assert(fuse::getEnumName<Color::kGreen>() == "kGreen");
        static_assert(fuse::getEnumName<Color::kBlue>() == "kBlue");

        EXPECT_EQ(fuse::getEnumName<Color::kRed>(), "kRed"sv);
        EXPECT_EQ(fuse::getEnumName<Color::kGreen>(), "kGreen"sv);
        EXPECT_EQ(fuse::getEnumName<Color::kBlue>(), "kBlue"sv);
    }

    // scoped enum
    {
        enum class Color : std::uint8_t { Red, Green, Blue };

        static_assert(fuse::getEnumName<Color::Red>() == "Red");
        static_assert(fuse::getEnumName<Color::Green>() == "Green");
        static_assert(fuse::getEnumName<Color::Blue>() == "Blue");

        EXPECT_EQ(fuse::getEnumName<Color::Red>(), "Red");
        EXPECT_EQ(fuse::getEnumName<Color::Green>(), "Green");
        EXPECT_EQ(fuse::getEnumName<Color::Blue>(), "Blue");
    }
}
