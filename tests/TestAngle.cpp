#include "GtestUtils.h"

#include <FuseCore/math/Angle.h>

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace fuse;
using namespace testing;

TEST(AngleTest, DefaultConstructor) {
    const Angle angle;
    EXPECT_EQ(angle.asDegrees(), 0.0f);
    EXPECT_EQ(angle.asRadians(), 0.0f);
}

TEST(AngleTest, ConstructFromDegrees) {
    const auto angle = fuse::degrees(180.0f);
    EXPECT_EQ(angle.asDegrees(), 180.0f);
    EXPECT_EQ(angle.asRadians(), std::numbers::pi_v<float>);
}

TEST(AngleTest, ConstructFromRadian) {
    const auto angle = fuse::radians(std::numbers::pi_v<float>);
    EXPECT_EQ(angle.asDegrees(), 180.0f);
    EXPECT_EQ(angle.asRadians(), std::numbers::pi_v<float>);
}

// operator-
TEST(Angle, negate) { EXPECT_EQ(-fuse::degrees(90.F), fuse::degrees(-90.F)); }

TEST(Angle, comparaison) {
    EXPECT_EQ(fuse::degrees(90.F), fuse::degrees(90.F)); // ==
    EXPECT_NE(fuse::degrees(90.F), fuse::degrees(91.F)); // !=
    EXPECT_LT(fuse::degrees(90.F), fuse::degrees(91.F)); // <
    EXPECT_LE(fuse::degrees(90.F), fuse::degrees(91.F)); // <=
    EXPECT_LE(fuse::degrees(91.F), fuse::degrees(91.F)); // <=
    EXPECT_GT(fuse::degrees(91.F), fuse::degrees(90.F)); // >
    EXPECT_GE(fuse::degrees(91.F), fuse::degrees(90.F)); // >=
    EXPECT_GE(fuse::degrees(91.F), fuse::degrees(91.F)); // >=
}

// Test addition operator
TEST(Angle, addition) {
    // operator+(Angle,Angle)
    const auto angle1 = fuse::degrees(90.F);
    const auto angle2 = fuse::degrees(45.F);
    EXPECT_EQ(angle1 + angle2, fuse::degrees(135.F));

    // operator+=(Angle)
    Angle angle = fuse::degrees(90.F);
    angle += fuse::degrees(45.F);
    EXPECT_EQ(angle, fuse::degrees(135.F));
}

// Test substact operator
TEST(Angle, substract) {
    // operator-(Angle,Angle)
    const auto angle1 = fuse::degrees(90.F);
    const auto angle2 = fuse::degrees(45.F);
    EXPECT_EQ(angle1 - angle2, fuse::degrees(45.F));

    // operator-=(Angle)
    Angle angle = fuse::degrees(90.F);
    angle -= fuse::degrees(45.F);
    EXPECT_EQ(angle, fuse::degrees(45.F));
}

// Test multiplication operator
TEST(Angle, multiply_by_scalar) {
    // operator*(Angle, float)
    EXPECT_EQ(fuse::degrees(90.F) * 2, fuse::degrees(180.F));

    // operator*(float, Angle)
    EXPECT_EQ(2 * fuse::degrees(90.F), fuse::degrees(180.F));

    // operator*=(float)
    Angle angle = fuse::degrees(45.F);
    angle *= 2;
    EXPECT_EQ(angle, fuse::degrees(90.F));
}

// Test multiplication operator
TEST(Angle, divide_by_scalar) {
    // operator/(Angle, float)
    EXPECT_EQ(fuse::degrees(90.F) / 2, fuse::degrees(45.F));

    // operator/=(float)
    Angle angle = fuse::degrees(90.F);
    angle /= 2;
    EXPECT_EQ(angle, fuse::degrees(45.F));
}

TEST(Angle, wrap) {
    EXPECT_THAT(fuse::degrees(0.F).wrap(), Eq(fuse::degrees(0.F)));

    // test positive angle in step of 45 fuse::degrees
    EXPECT_THAT(fuse::degrees(45.F).wrap(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(90.F).wrap(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(135.F).wrap(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(180.F).wrap(), Eq(fuse::degrees(180.F)));
    EXPECT_THAT(fuse::degrees(225.F).wrap(), Eq(fuse::degrees(225.F)));
    EXPECT_THAT(fuse::degrees(270.F).wrap(), Eq(fuse::degrees(270.F)));
    EXPECT_THAT(fuse::degrees(315.F).wrap(), Eq(fuse::degrees(315.F)));
    EXPECT_THAT(fuse::degrees(360.F).wrap(), Eq(fuse::degrees(0.F)));
    // do another turn with positive values
    EXPECT_THAT(fuse::degrees(405.F).wrap(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(450.F).wrap(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(495.F).wrap(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(540.F).wrap(), Eq(fuse::degrees(180.F)));
    EXPECT_THAT(fuse::degrees(585.F).wrap(), Eq(fuse::degrees(225.F)));
    EXPECT_THAT(fuse::degrees(630.F).wrap(), Eq(fuse::degrees(270.F)));
    EXPECT_THAT(fuse::degrees(675.F).wrap(), Eq(fuse::degrees(315.F)));
    EXPECT_THAT(fuse::degrees(720.F).wrap(), Eq(fuse::degrees(0.F)));

    // test negative angle in step of 45 fuse::degrees
    EXPECT_THAT(fuse::degrees(-45.F).wrap(), Eq(fuse::degrees(-45.F)));
    EXPECT_THAT(fuse::degrees(-90.F).wrap(), Eq(fuse::degrees(-90.F)));
    EXPECT_THAT(fuse::degrees(-135.F).wrap(), Eq(fuse::degrees(-135.F)));
    EXPECT_THAT(fuse::degrees(-180.F).wrap(), Eq(fuse::degrees(-180.F)));
    EXPECT_THAT(fuse::degrees(-225.F).wrap(), Eq(fuse::degrees(-225.F)));
    EXPECT_THAT(fuse::degrees(-270.F).wrap(), Eq(fuse::degrees(-270.F)));
    EXPECT_THAT(fuse::degrees(-315.F).wrap(), Eq(fuse::degrees(-315.F)));
    EXPECT_THAT(fuse::degrees(-360.F).wrap(), Eq(fuse::degrees(0.F)));
    // do another turn with negative values
    EXPECT_THAT(fuse::degrees(-405.F).wrap(), Eq(fuse::degrees(-45.F)));
    EXPECT_THAT(fuse::degrees(-450.F).wrap(), Eq(fuse::degrees(-90.F)));
    EXPECT_THAT(fuse::degrees(-495.F).wrap(), Eq(fuse::degrees(-135.F)));
    EXPECT_THAT(fuse::degrees(-540.F).wrap(), Eq(fuse::degrees(-180.F)));
    EXPECT_THAT(fuse::degrees(-585.F).wrap(), Eq(fuse::degrees(-225.F)));
    EXPECT_THAT(fuse::degrees(-630.F).wrap(), Eq(fuse::degrees(-270.F)));
    EXPECT_THAT(fuse::degrees(-675.F).wrap(), Eq(fuse::degrees(-315.F)));
    EXPECT_THAT(fuse::degrees(-720.F).wrap(), Eq(fuse::degrees(0.F)));
}

TEST(Angle, wrapSigned) {
    EXPECT_THAT(Angle::Zero.wrapSigned(), fuse::degrees(0.F));

    // test positive angle in step of 45 fuse::degrees
    EXPECT_THAT(fuse::degrees(45.F).wrapSigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(90.F).wrapSigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(135.F).wrapSigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(180.F).wrapSigned(), Eq(fuse::degrees(-180.F)));
    EXPECT_THAT(fuse::degrees(225.F).wrapSigned(), Eq(fuse::degrees(-135.F)));
    EXPECT_THAT(fuse::degrees(270.F).wrapSigned(), Eq(fuse::degrees(-90.F)));
    EXPECT_THAT(fuse::degrees(315.F).wrapSigned(), Eq(fuse::degrees(-45.F)));
    EXPECT_THAT(fuse::degrees(360.F).wrapSigned(), Eq(fuse::degrees(0.F)));
    // do another turn with positive values
    EXPECT_THAT(fuse::degrees(405.F).wrapSigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(450.F).wrapSigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(495.F).wrapSigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(540.F).wrapSigned(), Eq(fuse::degrees(-180.F)));
    EXPECT_THAT(fuse::degrees(585.F).wrapSigned(), Eq(fuse::degrees(-135.F)));
    EXPECT_THAT(fuse::degrees(630.F).wrapSigned(), Eq(fuse::degrees(-90.F)));
    EXPECT_THAT(fuse::degrees(675.F).wrapSigned(), Eq(fuse::degrees(-45.F)));
    EXPECT_THAT(fuse::degrees(720.F).wrapSigned(), Eq(fuse::degrees(0.F)));

    // test negative angle in step of 45 fuse::degrees
    EXPECT_THAT(fuse::degrees(-45.F).wrapSigned(), Eq(fuse::degrees(-45.F)));
    EXPECT_THAT(fuse::degrees(-90.F).wrapSigned(), Eq(fuse::degrees(-90.F)));
    EXPECT_THAT(fuse::degrees(-135.F).wrapSigned(), Eq(fuse::degrees(-135.F)));
    EXPECT_THAT(fuse::degrees(-180.F).wrapSigned(), Eq(fuse::degrees(-180.F)));
    EXPECT_THAT(fuse::degrees(-225.F).wrapSigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(-270.F).wrapSigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(-315.F).wrapSigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(-360.F).wrapSigned(), Eq(fuse::degrees(0.F)));
    // do another turn with negative values
    EXPECT_THAT(fuse::degrees(-405.F).wrapSigned(), Eq(fuse::degrees(-45.F)));
    EXPECT_THAT(fuse::degrees(-450.F).wrapSigned(), Eq(fuse::degrees(-90.F)));
    EXPECT_THAT(fuse::degrees(-495.F).wrapSigned(), Eq(fuse::degrees(-135.F)));
    EXPECT_THAT(fuse::degrees(-540.F).wrapSigned(), Eq(fuse::degrees(-180.F)));
    EXPECT_THAT(fuse::degrees(-585.F).wrapSigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(-630.F).wrapSigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(-675.F).wrapSigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(-720.F).wrapSigned(), Eq(fuse::degrees(0.F)));
}

TEST(Angle, wrapUnsigned) {
    EXPECT_THAT(fuse::degrees(0.F).wrapUnsigned(), Eq(fuse::degrees(0.F)));

    // test positive angle in step of 45 fuse::degrees
    EXPECT_THAT(fuse::degrees(45.F).wrapUnsigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(90.F).wrapUnsigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(135.F).wrapUnsigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(180.F).wrapUnsigned(), Eq(fuse::degrees(180.F)));
    EXPECT_THAT(fuse::degrees(225.F).wrapUnsigned(), Eq(fuse::degrees(225.F)));
    EXPECT_THAT(fuse::degrees(270.F).wrapUnsigned(), Eq(fuse::degrees(270.F)));
    EXPECT_THAT(fuse::degrees(315.F).wrapUnsigned(), Eq(fuse::degrees(315.F)));
    EXPECT_THAT(fuse::degrees(360.F).wrapUnsigned(), Eq(fuse::degrees(0.F)));
    // do another turn with positive values
    EXPECT_THAT(fuse::degrees(405.F).wrapUnsigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(450.F).wrapUnsigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(495.F).wrapUnsigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(540.F).wrapUnsigned(), Eq(fuse::degrees(180.F)));
    EXPECT_THAT(fuse::degrees(585.F).wrapUnsigned(), Eq(fuse::degrees(225.F)));
    EXPECT_THAT(fuse::degrees(630.F).wrapUnsigned(), Eq(fuse::degrees(270.F)));
    EXPECT_THAT(fuse::degrees(675.F).wrapUnsigned(), Eq(fuse::degrees(315.F)));
    EXPECT_THAT(fuse::degrees(720.F).wrapUnsigned(), Eq(fuse::degrees(0.F)));

    // test negative angle in step of 45 fuse::degrees
    EXPECT_THAT(fuse::degrees(-45.F).wrapUnsigned(), Eq(fuse::degrees(315.F)));
    EXPECT_THAT(fuse::degrees(-90.F).wrapUnsigned(), Eq(fuse::degrees(270.F)));
    EXPECT_THAT(fuse::degrees(-135.F).wrapUnsigned(), Eq(fuse::degrees(225.F)));
    EXPECT_THAT(fuse::degrees(-180.F).wrapUnsigned(), Eq(fuse::degrees(180.F)));
    EXPECT_THAT(fuse::degrees(-225.F).wrapUnsigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(-270.F).wrapUnsigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(-315.F).wrapUnsigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(-360.F).wrapUnsigned(), Eq(fuse::degrees(0.F)));
    // do another turn with negative values
    EXPECT_THAT(fuse::degrees(-405.F).wrapUnsigned(), Eq(fuse::degrees(315.F)));
    EXPECT_THAT(fuse::degrees(-450.F).wrapUnsigned(), Eq(fuse::degrees(270.F)));
    EXPECT_THAT(fuse::degrees(-495.F).wrapUnsigned(), Eq(fuse::degrees(225.F)));
    EXPECT_THAT(fuse::degrees(-540.F).wrapUnsigned(), Eq(fuse::degrees(180.F)));
    EXPECT_THAT(fuse::degrees(-585.F).wrapUnsigned(), Eq(fuse::degrees(135.F)));
    EXPECT_THAT(fuse::degrees(-630.F).wrapUnsigned(), Eq(fuse::degrees(90.F)));
    EXPECT_THAT(fuse::degrees(-675.F).wrapUnsigned(), Eq(fuse::degrees(45.F)));
    EXPECT_THAT(fuse::degrees(-720.F).wrapUnsigned(), Eq(fuse::degrees(0.F)));
}

// Test literal operator
TEST(Angle, operator_literal) {
    using namespace fuse::literals;
    ASSERT_EQ(180_deg, fuse::degrees(180.F));   // unsigned long long
    ASSERT_EQ(180.0_deg, fuse::degrees(180.F)); // long double

    ASSERT_EQ(1_rad, fuse::radians(1));      // unsigned long long
    ASSERT_EQ(1.2_rad, fuse::radians(1.2F)); // long double
}
