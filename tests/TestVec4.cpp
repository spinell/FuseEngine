#include <FuseCore/math/Vec4.h>
#include "GtestUtils.h"
#include <gtest/gtest.h>

using fuse::Vec4;
using namespace testing;

TEST(Vec4, constants) {
    EXPECT_FLOAT_EQ(Vec4::kZero.x, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kZero.y, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kZero.w, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kZero.z, 0.f);

    EXPECT_FLOAT_EQ(Vec4::kAxisX.x, 1.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisX.y, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisX.z, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisX.w, 0.f);

    EXPECT_FLOAT_EQ(Vec4::kAxisY.x, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisY.y, 1.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisY.z, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisY.w, 0.f);

    EXPECT_FLOAT_EQ(Vec4::kAxisZ.x, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisZ.y, 0.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisZ.z, 1.f);
    EXPECT_FLOAT_EQ(Vec4::kAxisZ.w, 0.f);
}

TEST(Vec4, ctor_from_components) {
    const Vec4 v(1, 2, 3, 4);
    EXPECT_FLOAT_EQ(v.x, 1.f);
    EXPECT_FLOAT_EQ(v.y, 2.f);
    EXPECT_FLOAT_EQ(v.z, 3.f);
    EXPECT_FLOAT_EQ(v.w, 4.f);
}

TEST(Vec4, add_vec_and_assign) {
    Vec4  v(1, 2, 3, 4);
    Vec4& r = v += Vec4(10, 20, 30, 40);

    EXPECT_FLOAT_EQ(v.x, 11.f);
    EXPECT_FLOAT_EQ(v.y, 22.f);
    EXPECT_FLOAT_EQ(v.z, 33.f);
    EXPECT_FLOAT_EQ(v.w, 44.f);

    EXPECT_FLOAT_EQ(r.x, 11.f);
    EXPECT_FLOAT_EQ(r.y, 22.f);
    EXPECT_FLOAT_EQ(r.z, 33.f);
    EXPECT_FLOAT_EQ(r.w, 44.f);
}

TEST(Vec4, sub_vec_and_assign) {
    Vec4  v(1, 2, 3, 4);
    Vec4& r = v -= Vec4(10, 20, 30, 40);

    EXPECT_FLOAT_EQ(v.x, -9.f);
    EXPECT_FLOAT_EQ(v.y, -18.f);
    EXPECT_FLOAT_EQ(v.z, -27.f);
    EXPECT_FLOAT_EQ(v.w, -36.f);

    EXPECT_FLOAT_EQ(r.x, -9.f);
    EXPECT_FLOAT_EQ(r.y, -18.f);
    EXPECT_FLOAT_EQ(r.z, -27.f);
    EXPECT_FLOAT_EQ(r.w, -36.f);
}

TEST(Vec4, mul_scalar_and_assign) {
    Vec4  v(1, 2, 3, 4);
    Vec4& r = v *= 2.f;

    EXPECT_FLOAT_EQ(v.x, 2.f);
    EXPECT_FLOAT_EQ(v.y, 4.f);
    EXPECT_FLOAT_EQ(v.z, 6.f);
    EXPECT_FLOAT_EQ(v.w, 8.f);

    EXPECT_FLOAT_EQ(r.x, 2.f);
    EXPECT_FLOAT_EQ(r.y, 4.f);
    EXPECT_FLOAT_EQ(r.z, 6.f);
    EXPECT_FLOAT_EQ(r.w, 8.f);
}

TEST(Vec4, div_scalar_and_assign) {
    Vec4  v(10, 20, 30, 40);
    Vec4& r = v /= 2.f;

    EXPECT_FLOAT_EQ(v.x, 5.f);
    EXPECT_FLOAT_EQ(v.y, 10.f);
    EXPECT_FLOAT_EQ(v.z, 15.f);
    EXPECT_FLOAT_EQ(v.w, 20.f);

    EXPECT_FLOAT_EQ(r.x, 5.f);
    EXPECT_FLOAT_EQ(r.y, 10.f);
    EXPECT_FLOAT_EQ(r.z, 15.f);
    EXPECT_FLOAT_EQ(r.w, 20.f);
}

TEST(Vec4, add_vec) {
    EXPECT_EQ(Vec4(1, 2, 3, 4) + Vec4(1, 0, 0, 0), Vec4(2, 2, 3, 4));
    EXPECT_EQ(Vec4(1, 2, 3, 4) + Vec4(0, 1, 0, 0), Vec4(1, 3, 3, 4));
    EXPECT_EQ(Vec4(1, 2, 3, 4) + Vec4(0, 0, 1, 0), Vec4(1, 2, 4, 4));
    EXPECT_EQ(Vec4(1, 2, 3, 4) + Vec4(0, 0, 0, 1), Vec4(1, 2, 3, 5));
}

TEST(Vec4, sub_vec) {
    EXPECT_EQ(Vec4(1, 2, 3, 4) - Vec4(1, 0, 0, 0), Vec4(0, 2, 3, 4));
    EXPECT_EQ(Vec4(1, 2, 3, 4) - Vec4(0, 1, 0, 0), Vec4(1, 1, 3, 4));
    EXPECT_EQ(Vec4(1, 2, 3, 4) - Vec4(0, 0, 1, 0), Vec4(1, 2, 2, 4));
    EXPECT_EQ(Vec4(1, 2, 3, 4) - Vec4(0, 0, 0, 1), Vec4(1, 2, 3, 3));
}

TEST(Vec4, mul_scalar) {
    EXPECT_EQ(Vec4(1, 2, 3, 4) * 2, Vec4(2, 4, 6, 8));
    EXPECT_EQ(2 * Vec4(1, 2, 3, 4), Vec4(2, 4, 6, 8));
}

TEST(Vec4, div_scalar) {
    EXPECT_EQ(Vec4(10, 20, 30, 40) / 2, Vec4(5, 10, 15, 20));
}

TEST(Vec4, dotProduct) {
    const Vec4 v1(1, 2, 3, 4);
    const Vec4 v2(5, 6, 7, 8);
    EXPECT_FLOAT_EQ(v1.dotProduct(v2), 70.f);
}
