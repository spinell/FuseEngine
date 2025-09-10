#include "GtestUtils.h"

#include <FuseCore/math/Angle.h>
#include <FuseCore/math/Mat4.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>

using fuse::Mat4;
using fuse::Vec3;
using fuse::Vec4;
using namespace testing;

namespace {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
MATCHER_P(almostEquals, rhs, "") { return arg.isAlmostEquals(rhs); }

} // namespace

TEST(Mat4, constant) {
    EXPECT_EQ(Mat4::kZero(0, 0), 0);
    EXPECT_EQ(Mat4::kZero(0, 1), 0);
    EXPECT_EQ(Mat4::kZero(0, 2), 0);
    EXPECT_EQ(Mat4::kZero(0, 3), 0);
    EXPECT_EQ(Mat4::kZero(1, 0), 0);
    EXPECT_EQ(Mat4::kZero(1, 1), 0);
    EXPECT_EQ(Mat4::kZero(1, 2), 0);
    EXPECT_EQ(Mat4::kZero(1, 3), 0);
    EXPECT_EQ(Mat4::kZero(2, 0), 0);
    EXPECT_EQ(Mat4::kZero(2, 1), 0);
    EXPECT_EQ(Mat4::kZero(2, 2), 0);
    EXPECT_EQ(Mat4::kZero(2, 3), 0);
    EXPECT_EQ(Mat4::kZero(3, 0), 0);
    EXPECT_EQ(Mat4::kZero(3, 1), 0);
    EXPECT_EQ(Mat4::kZero(3, 2), 0);
    EXPECT_EQ(Mat4::kZero(3, 3), 0);

    EXPECT_EQ(Mat4::kIdentity(0, 0), 1);
    EXPECT_EQ(Mat4::kIdentity(0, 1), 0);
    EXPECT_EQ(Mat4::kIdentity(0, 2), 0);
    EXPECT_EQ(Mat4::kIdentity(0, 3), 0);
    EXPECT_EQ(Mat4::kIdentity(1, 0), 0);
    EXPECT_EQ(Mat4::kIdentity(1, 1), 1);
    EXPECT_EQ(Mat4::kIdentity(1, 2), 0);
    EXPECT_EQ(Mat4::kIdentity(1, 3), 0);
    EXPECT_EQ(Mat4::kIdentity(2, 0), 0);
    EXPECT_EQ(Mat4::kIdentity(2, 1), 0);
    EXPECT_EQ(Mat4::kIdentity(2, 2), 1);
    EXPECT_EQ(Mat4::kIdentity(2, 3), 0);
    EXPECT_EQ(Mat4::kIdentity(3, 0), 0);
    EXPECT_EQ(Mat4::kIdentity(3, 1), 0);
    EXPECT_EQ(Mat4::kIdentity(3, 2), 0);
    EXPECT_EQ(Mat4::kIdentity(3, 3), 1);
}

/// ===================================================
/// ============      Constructors          ===========
/// ===================================================

// test constructor with c-style array
TEST(Mat4, ctor_which_values) {
    const auto  mat        = Mat4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    const float expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    EXPECT_THAT(std::span<const float>(mat.ptr(), 16), ElementsAreArray(expected, 16));
}

// test constructor with c-style array
TEST(Mat4, ctor_with_raw_data) {
    const float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const auto  mat    = Mat4(data);
    EXPECT_THAT(std::span<const float>(mat.ptr(), 16), ElementsAreArray(data, 16));
}

// test constructor with c-style array
TEST(Mat4, ctor_with_pointer) {
    const std::vector<float> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const auto               mat  = Mat4(data.data());
    EXPECT_THAT(std::span<const float>(mat.ptr(), 16), ElementsAreArray(data));
}

// test constructor with 4 Vec4
TEST(Mat4, ctor_with_vec4) {
    const auto row1 = Vec4(1.F, 2.F, 3.F, 4.F);
    const auto row2 = Vec4(5.F, 6.F, 7.F, 8.F);
    const auto row3 = Vec4(9.F, 10.F, 11.F, 12.F);
    const auto row4 = Vec4(13.F, 14.F, 15.F, 16.F);
    const auto mat  = Mat4(row1, row2, row3, row4);

    auto expected =
      {1.F, 2.F, 3.F, 4.F, 5.F, 6.F, 7.F, 8.F, 9.F, 10.F, 11.F, 12.F, 13.F, 14.F, 15.F, 16.F};
    EXPECT_THAT(std::span<const float>(mat.ptr(), 16), ElementsAreArray(expected));
}

/// ===================================================
/// ==============  Arithmethic Operator    ===========
/// ===================================================

// test scalare * mat and mat * scalar
TEST(Mat4, multiplyByScalar) {
    const float data[16] =
      {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f};
    const auto expected =
      {0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f};
    const auto multiplyBy = 2.F;
    const Mat4 mat(data);
    const Mat4 result1 = mat * multiplyBy;
    const Mat4 result2 = multiplyBy * mat;
    EXPECT_THAT(std::span<const float>(result1.ptr(), 16), ElementsAreArray(expected));
    EXPECT_THAT(std::span<const float>(result2.ptr(), 16), ElementsAreArray(expected));
}

// test mat * mat
TEST(Mat4, multiplyByMatrix) {
    const float data1[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const float data2[16] = {3, 4, 7, 0, 9, 12, 2, 7, 8, 5, 6, 13, 15, 22, 26, 4};
    const Mat4  matrix1(data1);
    const Mat4  matrix2(data2);
    const Mat4  result = matrix1 * matrix2;
    EXPECT_EQ(result(0, 0), 70);
    EXPECT_EQ(result(0, 1), 88);
    EXPECT_EQ(result(0, 2), 92);
    EXPECT_EQ(result(0, 3), 45);
    EXPECT_EQ(result(1, 0), 210);
    EXPECT_EQ(result(1, 1), 260);
    EXPECT_EQ(result(1, 2), 256);
    EXPECT_EQ(result(1, 3), 141);
    EXPECT_EQ(result(2, 0), 350);
    EXPECT_EQ(result(2, 1), 432);
    EXPECT_EQ(result(2, 2), 420);
    EXPECT_EQ(result(2, 3), 237);
    EXPECT_EQ(result(3, 0), 490);
    EXPECT_EQ(result(3, 1), 604);
    EXPECT_EQ(result(3, 2), 584);
    EXPECT_EQ(result(3, 3), 333);
}

/// ===================================================
///                 Other functions
/// ===================================================
TEST(Mat4, determinant) {
    const auto row1 = Vec4(0.f, 1.f, 2.f, 3.f);
    const auto row2 = Vec4(4.f, 5.f, 6.f, 7.f);
    const auto row3 = Vec4(8.f, 9.f, 10.f, 11.f);
    const auto row4 = Vec4(12.f, 13.f, 14.f, 15.f);
    Mat4       matrix(row1, row2, row3, row4);

    EXPECT_FLOAT_EQ(matrix.determinant(), 0);

    matrix(0, 0) = 2;
    matrix(2, 1) = 3;
    EXPECT_FLOAT_EQ(matrix.determinant(), -96);
}

TEST(Mat4, isAffine) {
    EXPECT_TRUE(Mat4::kIdentity.isAffine());

    // the first 3 colum of the last row must be 0
    // to be affine, so just put another value than 0.
    for (unsigned i = 0; i < 3; i++) {
        Mat4 mat  = Mat4::kIdentity;
        mat(3, i) = 1;
        EXPECT_FALSE(mat.isAffine());
    }

    // The last collum of the last row must be 1 to be affine.
    // so just put another value than 1.
    Mat4 mat  = Mat4::kIdentity;
    mat(3, 3) = 10;
    EXPECT_FALSE(mat.isAffine());
}

TEST(Mat4, tranpose) {
    Mat4 mat(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    mat.transpose();
    // check col 0
    EXPECT_EQ(mat(0, 0), 0);
    EXPECT_EQ(mat(1, 0), 1);
    EXPECT_EQ(mat(2, 0), 2);
    EXPECT_EQ(mat(3, 0), 3);

    // check col 1
    EXPECT_EQ(mat(0, 1), 4);
    EXPECT_EQ(mat(1, 1), 5);
    EXPECT_EQ(mat(2, 1), 6);
    EXPECT_EQ(mat(3, 1), 7);

    // check col 2
    EXPECT_EQ(mat(0, 2), 8);
    EXPECT_EQ(mat(1, 2), 9);
    EXPECT_EQ(mat(2, 2), 10);
    EXPECT_EQ(mat(3, 2), 11);

    // check col 3
    EXPECT_EQ(mat(0, 3), 12);
    EXPECT_EQ(mat(1, 3), 13);
    EXPECT_EQ(mat(2, 3), 14);
    EXPECT_EQ(mat(3, 3), 15);
}

TEST(Mat4, tranposed) {
    const Mat4 mat(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    auto       m = mat.transposed();
    // check col 0
    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(1, 0), 1);
    EXPECT_EQ(m(2, 0), 2);
    EXPECT_EQ(m(3, 0), 3);

    // check col 1
    EXPECT_EQ(m(0, 1), 4);
    EXPECT_EQ(m(1, 1), 5);
    EXPECT_EQ(m(2, 1), 6);
    EXPECT_EQ(m(3, 1), 7);

    // check col 2
    EXPECT_EQ(m(0, 2), 8);
    EXPECT_EQ(m(1, 2), 9);
    EXPECT_EQ(m(2, 2), 10);
    EXPECT_EQ(m(3, 2), 11);

    // check col 3
    EXPECT_EQ(m(0, 3), 12);
    EXPECT_EQ(m(1, 3), 13);
    EXPECT_EQ(m(2, 3), 14);
    EXPECT_EQ(m(3, 3), 15);
}

TEST(Mat4, inversed) {
    EXPECT_EQ(Mat4::kIdentity.inversed() * Mat4::kIdentity, Mat4::kIdentity);

    const Mat4 mat(2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 15);
    EXPECT_THAT(mat.inversed() * mat, almostEquals(Mat4::kIdentity));

    {
        const float data[16] = {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 15};
        const Mat4  matrix(data);
        Mat4        result = matrix.inversed();
        EXPECT_FLOAT_EQ(result(0, 0), 0.5f);
        EXPECT_FLOAT_EQ(result(0, 1), -1.0f);
        EXPECT_FLOAT_EQ(result(0, 2), 0.5f);
        EXPECT_FLOAT_EQ(result(0, 3), 0.0f);
        EXPECT_FLOAT_EQ(result(1, 0), -0.75f);
        EXPECT_FLOAT_EQ(result(1, 1), 0.163461551f);
        EXPECT_FLOAT_EQ(result(1, 2), 0.0480769239f);
        EXPECT_FLOAT_EQ(result(1, 3), 0.0384615399f);
        EXPECT_FLOAT_EQ(result(2, 0), 0.0f);
        EXPECT_FLOAT_EQ(result(2, 1), -0.0769230798f);
        EXPECT_FLOAT_EQ(result(2, 2), 0.153846160f);
        EXPECT_FLOAT_EQ(result(2, 3), -0.0769230798f);
        EXPECT_FLOAT_EQ(result(3, 0), 0.25f);
        EXPECT_FLOAT_EQ(result(3, 1), 0.663461566f);
        EXPECT_FLOAT_EQ(result(3, 2), -0.451923102f);
        EXPECT_FLOAT_EQ(result(3, 3), 0.0384615399f);
    }

    {
        const float data[16] = {1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1};
        const Mat4  matrix(data);
        Mat4        result = matrix.inversed();
        EXPECT_FLOAT_EQ(result(0, 0), 1.0f);
        EXPECT_FLOAT_EQ(result(0, 1), 0.0f);
        EXPECT_FLOAT_EQ(result(0, 2), 0.0f);
        EXPECT_FLOAT_EQ(result(0, 3), -1.0f);
        EXPECT_FLOAT_EQ(result(1, 0), 0.0f);
        EXPECT_FLOAT_EQ(result(1, 1), 1.0f);
        EXPECT_FLOAT_EQ(result(1, 2), 0.0f);
        EXPECT_FLOAT_EQ(result(1, 3), -2.0f);
        EXPECT_FLOAT_EQ(result(2, 0), 0.0f);
        EXPECT_FLOAT_EQ(result(2, 1), 0.0f);
        EXPECT_FLOAT_EQ(result(2, 2), 1.0f);
        EXPECT_FLOAT_EQ(result(2, 3), -3.0f);
        EXPECT_FLOAT_EQ(result(3, 0), 0.0f);
        EXPECT_FLOAT_EQ(result(3, 1), 0.0f);
        EXPECT_FLOAT_EQ(result(3, 2), 0.0f);
        EXPECT_FLOAT_EQ(result(3, 3), 1.0f);
    }
}

/// ===================================================
///                 Transform functions
/// ===================================================


//
// Test CreateTranslation()
//
// This should result as the fallowing matrix.
//
//	0  0   0  tX
//  0  0   0  tY
//  0  0   0  tZ
//  0  0   0   1
//
TEST(Mat4, createTranslation) {
    const auto trans = Mat4::CreateTranslation({2, 3, 4});
    EXPECT_EQ(trans.getRow(0), Vec4(1, 0, 0, 2));
    EXPECT_EQ(trans.getRow(1), Vec4(0, 1, 0, 3));
    EXPECT_EQ(trans.getRow(2), Vec4(0, 0, 1, 4));
    EXPECT_EQ(trans.getRow(3), Vec4(0, 0, 0, 1));

    EXPECT_EQ(Mat4::CreateTranslation({1, 0, 0}) * Vec4(1, 1, 1, 1), Vec4(2, 1, 1, 1));
    EXPECT_EQ(Mat4::CreateTranslation({0, 1, 0}) * Vec4(1, 1, 1, 1), Vec4(1, 2, 1, 1));
    EXPECT_EQ(Mat4::CreateTranslation({0, 0, 1}) * Vec4(1, 1, 1, 1), Vec4(1, 1, 2, 1));
}

//
// Test the CreateScaling function
//
// This should result as the fallowing matrix.
//
//	sX    0	  0   0
//  0    sY   0   0
//  0     0  sZ   0
//  0     0   0   1
//
TEST(Mat4, createScaling) {
    const auto scale = Mat4::CreateScaling({2, 3, 4});
    EXPECT_EQ(scale.getCol(0), Vec4(2, 0, 0, 0));
    EXPECT_EQ(scale.getCol(1), Vec4(0, 3, 0, 0));
    EXPECT_EQ(scale.getCol(2), Vec4(0, 0, 4, 0));
    EXPECT_EQ(scale.getCol(3), Vec4(0, 0, 0, 1));

    EXPECT_EQ(Mat4::CreateScaling({2, 0, 0}) * Vec4(1, 1, 1, 1), Vec4(2, 0, 0, 1));
    EXPECT_EQ(Mat4::CreateScaling({0, 2, 0}) * Vec4(1, 1, 1, 1), Vec4(0, 2, 0, 1));
    EXPECT_EQ(Mat4::CreateScaling({0, 0, 2}) * Vec4(1, 1, 1, 1), Vec4(0, 0, 2, 1));
}

//
// Test the CreateRotationX function (rotation around X-axis)
//
// This should result as the fallowing matrix.
//
//	1     0			 0         0
//  0  cos(angle) -sin(angle)  0
//  0  sin(angle)  cos(angle)  0
//  0     0          0         1
//
TEST(Mat4, CreateRotationX) {
    {
        const auto  angle    = fuse::degrees(45.f);
        const float sinAngle = std::sin(angle);
        const float cosAngle = std::cos(angle);
        const auto  rot      = Mat4::CreateRotationX(angle);
        EXPECT_EQ(rot.getCol(0), Vec4(1, 0, 0, 0));
        EXPECT_EQ(rot.getCol(1), Vec4(0, cosAngle, sinAngle, 0));
        EXPECT_EQ(rot.getCol(2), Vec4(0, -sinAngle, cosAngle, 0));
        EXPECT_EQ(rot.getCol(3), Vec4(0, 0, 0, 1));
    }

    // [0,0,-1] should become [0,1,0]
    {
        const auto rot    = Mat4::CreateRotationX(fuse::degrees(90.f));
        const auto result = rot * Vec4(0, 0, -1, 1);
        EXPECT_FLOAT_EQ(result.x, 0.0f);
        EXPECT_FLOAT_EQ(result.y, 1.0f);
        EXPECT_NEAR(result.z, 0.0f, std::numeric_limits<float>::epsilon());
        EXPECT_FLOAT_EQ(result.w, 1.0f);
    }

    // [0,1,0] should become [0,0,1]
    {
        const auto rot    = Mat4::CreateRotationX(fuse::degrees(90.f));
        const auto result = rot * Vec4(0, 1, 0, 1);
        EXPECT_FLOAT_EQ(result.x, 0.0f);
        EXPECT_NEAR(result.y, 0.0f, std::numeric_limits<float>::epsilon());
        EXPECT_FLOAT_EQ(result.z, 1.0f);
        EXPECT_FLOAT_EQ(result.w, 1.0f);
    }
}

//
// Test the CreateRotationY function (rotation around y-axis)
//
// This should result as the fallowing matrix.
//
//	cos(angle)     0	sin(angle)  0
//      0		   1		0		0
// -sin(angle)     0    cos(angle)  0
//      0          0        0       1
//
TEST(Mat4, CreateRotationY) {
    {
        const auto  angle    = fuse::degrees(45.f);
        const float sinAngle = std::sin(angle);
        const float cosAngle = std::cos(angle);
        const auto  rot      = Mat4::CreateRotationY(angle);
        EXPECT_EQ(rot.getCol(0), Vec4(cosAngle, 0, -sinAngle, 0));
        EXPECT_EQ(rot.getCol(1), Vec4(0, 1, 0, 0));
        EXPECT_EQ(rot.getCol(2), Vec4(sinAngle, 0, cosAngle, 0));
        EXPECT_EQ(rot.getCol(3), Vec4(0, 0, 0, 1));
    }

    // [0,0,-1] should become [-1,0,0]
    {
        const auto rot    = Mat4::CreateRotationY(fuse::degrees(90.f));
        const auto result = rot * Vec4(0, 0, -1, 1);
        EXPECT_FLOAT_EQ(result.x, -1.0f);
        EXPECT_FLOAT_EQ(result.y, 0.0f);
        EXPECT_NEAR(result.z, 0.0f, std::numeric_limits<float>::epsilon());
        EXPECT_FLOAT_EQ(result.w, 1.0f);
    }
}

//
// Test the CreateRotationZ function (rotation around z-axis)
//
// This should result as the fallowing matrix.
//
//	cos(angle) -sin(angle)	0   0
//  sin(angle)	cos(angle)	0	0
//      0          0        1   0
//      0          0        0   1
//
TEST(Mat4, CreateRotationZ) {
    {
        const auto  angle    = fuse::degrees(45.f);
        const float sinAngle = std::sin(angle);
        const float cosAngle = std::cos(angle);
        const auto  rot      = Mat4::CreateRotationZ(angle);
        EXPECT_EQ(rot.getCol(0), Vec4(cosAngle, sinAngle, 0, 0));
        EXPECT_EQ(rot.getCol(1), Vec4(-sinAngle, cosAngle, 0, 0));
        EXPECT_EQ(rot.getCol(2), Vec4(0, 0, 1, 0));
        EXPECT_EQ(rot.getCol(3), Vec4(0, 0, 0, 1));
    }

    // [1,0,0] should become [0,1,0]
    {
        const auto rot    = Mat4::CreateRotationZ(fuse::degrees(90.f));
        const auto result = rot * Vec4(1, 0, 0, 1);
        EXPECT_NEAR(result.x, 0.0f, std::numeric_limits<float>::epsilon());
        EXPECT_FLOAT_EQ(result.y, 1.0f);
        EXPECT_FLOAT_EQ(result.z, 0.0f);
        EXPECT_FLOAT_EQ(result.w, 1.0f);
    }
}

TEST(Mat4, CreateRotation_angleAxis) {
    //
    // Test with a angle around x-axis
    // The rotation matrix must match the one create by CreateRotationX()
    //
    {
        const auto angle  = fuse::degrees(45);
        const auto result = Mat4::CreateRotationX(angle);
        const auto rot    = Mat4::CreateRotation(angle, Vec3::kAxisX);
        EXPECT_TRUE(rot == result);
    }

    //
    // Test with a angle around y-axis
    // The rotation matrix must match the one create by CreateRotationY()
    //
    {
        const auto angle  = fuse::degrees(45);
        const auto result = Mat4::CreateRotationY(angle);
        const auto rot    = Mat4::CreateRotation(angle, Vec3::kAxisY);
        EXPECT_TRUE(rot == result);
    }

    //
    // Test with a angle around Z-axis
    // The rotation matrix must match the one create by CreateRotationZ()
    //
    {
        const auto angle  = fuse::degrees(45);
        const auto result = Mat4::CreateRotationZ(angle);
        const auto rot    = Mat4::CreateRotation(angle, Vec3::kAxisZ);
        EXPECT_TRUE(rot == result);
    }
}

/// ===================================================
///                    View
/// ===================================================
TEST(Mat4, CreateViewLookAt) {

    // Test without translation and without rotation
    // camera at [0,0,0] looking in front at point [0,0,-1]
    // Every point should remain the same
    {
        const auto view = Mat4::CreateViewLookAt({0, 0, 0}, {0, 0, -1}, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0, 0,  0, 1), Vec4( 0,  0,  0, 1));
        EXPECT_EQ(view * Vec4(10, 0, 10, 1), Vec4(10,  0, 10, 1));
        EXPECT_EQ(view * Vec4(0, 10, 10, 1), Vec4( 0, 10, 10, 1));
        EXPECT_EQ(view * Vec4(0,  0, 10, 1), Vec4( 0,  0, 10, 1));
        // clang-format on
    }

    // Test translation on x-axis
    // camera at [10,0,0] looking in front at point [10,0,-1]
    // Every point should been translated by [-10,0,0]
    {
        const auto view = Mat4::CreateViewLookAt({10, 0, 0}, {10, 0, -1}, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0,  0,  0, 1), Vec4(-10,  0,   0, 1));
        EXPECT_EQ(view * Vec4(10,  0, 10, 1), Vec4( -0,  0,  10, 1));
        EXPECT_EQ(view * Vec4( 0, 10, 10, 1), Vec4(-10, 10,  10, 1));
        EXPECT_EQ(view * Vec4( 0,  0, 10, 1), Vec4(-10,  0,  10, 1));
        // clang-format on
    }

    // Test translation on y-axis
    // camera at [0,10,0] looking in front at point [0,10,-1]
    // Every point should been translated by [0,-10,0]
    {
        const auto view = Mat4::CreateViewLookAt({0, 10, 0}, {0, 10, -1}, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0,  0,  0, 1), Vec4(  0, -10,  0, 1));
        EXPECT_EQ(view * Vec4(10,  0, 10, 1), Vec4( 10, -10, 10, 1));
        EXPECT_EQ(view * Vec4( 0, 10, 10, 1), Vec4(  0,   0, 10, 1));
        EXPECT_EQ(view * Vec4( 0,  0, 10, 1), Vec4(  0, -10, 10, 1));
        // clang-format on
    }

    // Test translation on z-axis
    // camera at [0,0,10] looking in front at point [0,0,0]
    // Every point should been translated by [0,0,-10]
    {
        const auto view = Mat4::CreateViewLookAt({0, 0, 10}, Vec3::kZero, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0, 0,  0, 1), Vec4( 0,  0, -10, 1));
        EXPECT_EQ(view * Vec4(10, 0, 10, 1), Vec4(10,  0,   0, 1));
        EXPECT_EQ(view * Vec4(0, 10, 10, 1), Vec4( 0, 10,   0, 1));
        EXPECT_EQ(view * Vec4(0,  0, 10, 1), Vec4( 0,  0,   0, 1));
        // clang-format on
    }

    // Test rotation around y-axis
    // camera at [0,0,0] looking in front at point [-1,0,0]
    // Every point should been rotated by 90 degrees clockwise around y-axis
    {
        const auto view = Mat4::CreateViewLookAt({0, 0, 0}, {-1, 0, 0}, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0, 0,  0, 1), Vec4( 0, 0,  0, 1));
        EXPECT_EQ(view * Vec4( 0, 0,-10, 1), Vec4(10, 0,  0, 1));
        EXPECT_EQ(view * Vec4(10, 0,  0, 1), Vec4( 0, 0, 10, 1));
        // clang-format on
    }
}

TEST(Mat4, CreateViewLookTo) {

    // normalized direction should be the same as non normalized direction
    EXPECT_EQ(Mat4::CreateViewLookTo({0, 0, 0}, {0,0,-1}, Vec3::kAxisY),
              Mat4::CreateViewLookTo({0, 0, 0}, {0,0,-10}, Vec3::kAxisY));

    // Test without translation and without rotation
    // camera at [0,0,0] looking at direction [0,0,-1]
    // Every point should remain the same
    {
        const auto view = Mat4::CreateViewLookTo({0, 0, 0}, Vec3::kAxisZNeg, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0, 0,  0, 1), Vec4( 0,  0,  0, 1));
        EXPECT_EQ(view * Vec4(10, 0, 10, 1), Vec4(10,  0, 10, 1));
        EXPECT_EQ(view * Vec4(0, 10, 10, 1), Vec4( 0, 10, 10, 1));
        EXPECT_EQ(view * Vec4(0,  0, 10, 1), Vec4( 0,  0, 10, 1));
        // clang-format on
    }

    // Test translation on x-axis
    // camera at [10,0,0] looking at direction [0,0,-1]
    // Every point should been translated by [-10,0,0]
    {
        const auto view = Mat4::CreateViewLookTo({10, 0, 0}, Vec3::kAxisZNeg, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0,  0,  0, 1), Vec4(-10,  0,   0, 1));
        EXPECT_EQ(view * Vec4(10,  0, 10, 1), Vec4( -0,  0,  10, 1));
        EXPECT_EQ(view * Vec4( 0, 10, 10, 1), Vec4(-10, 10,  10, 1));
        EXPECT_EQ(view * Vec4( 0,  0, 10, 1), Vec4(-10,  0,  10, 1));
        // clang-format on
    }

    // Test translation on y-axis
    // camera at [0,10,0] looking at direction [0,0,-1]
    // Every point should been translated by [0,-10,0]
    {
        const auto view = Mat4::CreateViewLookTo({0, 10, 0}, Vec3::kAxisZNeg, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0,  0,  0, 1), Vec4(  0, -10,  0, 1));
        EXPECT_EQ(view * Vec4(10,  0, 10, 1), Vec4( 10, -10, 10, 1));
        EXPECT_EQ(view * Vec4( 0, 10, 10, 1), Vec4(  0,   0, 10, 1));
        EXPECT_EQ(view * Vec4( 0,  0, 10, 1), Vec4(  0, -10, 10, 1));
        // clang-format on
    }

    // Test translation on z-axis
    // camera at [0,0,10] looking at direction [0,0,-1]
    // Every point should been translated by [0,0,-10]
    {
        const auto view = Mat4::CreateViewLookTo({0, 0, 10}, Vec3::kAxisZNeg, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0, 0,  0, 1), Vec4( 0,  0, -10, 1));
        EXPECT_EQ(view * Vec4(10, 0, 10, 1), Vec4(10,  0,   0, 1));
        EXPECT_EQ(view * Vec4(0, 10, 10, 1), Vec4( 0, 10,   0, 1));
        EXPECT_EQ(view * Vec4(0,  0, 10, 1), Vec4( 0,  0,   0, 1));
        // clang-format on
    }

    // Test rotation around y-axis
    // camera at [0,0,0] looking at direction [-1,0,0]
    // Every point should been rotated by 90 degrees clockwise around y-axis
    {
        const auto view = Mat4::CreateViewLookTo({0, 0, 0}, Vec3::kAxisXNeg, Vec3::kAxisY);
        // clang-format off
        EXPECT_EQ(view * Vec4( 0, 0,  0, 1), Vec4( 0, 0,  0, 1));
        EXPECT_EQ(view * Vec4( 0, 0,-10, 1), Vec4(10, 0,  0, 1));
        EXPECT_EQ(view * Vec4(10, 0,  0, 1), Vec4( 0, 0, 10, 1));
        // clang-format on
    }
}

/// ===================================================
///                 Projection
/// ===================================================


TEST(Mat4, CreateProjectionOrthographicOffCenter) {
    // view volume unit cube x (-1, 1) y (-1, 1) z (-1, 1)
    // should be a no operation except flipping Z because the matrix use OpenGL
    // standard (+Z poiting into the screen).
    {
        const auto proj = Mat4::CreateProjectionOrthographicOffCenter(-1, 1, -1, 1, -1, 1);
        // clang-format off
        EXPECT_THAT(proj * Vec4( 0,  0,  0, 1), Eq(Vec4( 0,  0,  0.f, 1.f)));
        EXPECT_THAT(proj * Vec4( 1,  0,  0, 1), Eq(Vec4( 1,  0,  0.f, 1.f)));
        EXPECT_THAT(proj * Vec4(-1,  0,  0, 1), Eq(Vec4(-1,  0,  0.f, 1.f)));
        EXPECT_THAT(proj * Vec4( 0,  1,  0, 1), Eq(Vec4( 0,  1,  0.f, 1.f)));
        EXPECT_THAT(proj * Vec4( 0, -1,  0, 1), Eq(Vec4( 0, -1,  0.f, 1.f)));
        EXPECT_THAT(proj * Vec4( 0,  0,  1, 1), Eq(Vec4( 0,  0, -1.f, 1.f)));
        EXPECT_THAT(proj * Vec4( 0,  0, -1, 1), Eq(Vec4( 0,  0,  1.f, 1.f)));
        // clang-format on
    }
    // view volume x (0, 10) y (0, 5) z (0, 8)
    // standard (+Z poiting into the screen).
    {
        // clang-format off
        const auto proj = Mat4::CreateProjectionOrthographicOffCenter(0, 10, 0, 5, 0, 4);
        EXPECT_THAT(proj * Vec4( 0, 0, 0, 1), Eq(Vec4(-1, -1, -1.f,  1.f)));
        EXPECT_THAT(proj * Vec4( 5, 0, 0, 1), Eq(Vec4( 0, -1, -1.f,  1.f)));
        EXPECT_THAT(proj * Vec4(10, 0, 0, 1), Eq(Vec4( 1, -1, -1.f,  1.f)));
        EXPECT_THAT(proj * Vec4(11, 0, 0, 1), Eq(Vec4(1.2f,-1, -1.f,  1.f)));
        EXPECT_THAT(proj * Vec4( 0, 5, 0, 1), Eq(Vec4(-1,  1, -1.f,  1.f)));
        EXPECT_THAT(proj * Vec4( 0, 0,-2, 1), Eq(Vec4(-1, -1,  0.0f, 1.f)));
        EXPECT_THAT(proj * Vec4( 0, 0,-3, 1), Eq(Vec4(-1, -1,  0.5f, 1.f)));
        EXPECT_THAT(proj * Vec4( 0, 0,-4, 1), Eq(Vec4(-1, -1,  1.f,  1.f)));
        EXPECT_THAT(proj * Vec4( 0, 0,-5, 1), Eq(Vec4(-1, -1,  1.5f, 1.f)));
        EXPECT_THAT(proj * Vec4( 0, 0,-8, 1), Eq(Vec4(-1, -1,  3.f,  1.f)));
        // clang-format on
    }
}
