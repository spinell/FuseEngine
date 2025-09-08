#include "Mat4.h"

#include "Angle.h"

#include <cmath>

namespace {

inline float matMinor(const fuse::Mat4& mat,
                      unsigned          r0,
                      unsigned          r1,
                      unsigned          r2,
                      unsigned          c0,
                      unsigned          c1,
                      unsigned          c2) {
    return mat(r0, c0) * (mat(r1, c1) * mat(r2, c2) - mat(r2, c1) * mat(r1, c2)) -
           mat(r0, c1) * (mat(r1, c0) * mat(r2, c2) - mat(r2, c0) * mat(r1, c2)) +
           mat(r0, c2) * (mat(r1, c0) * mat(r2, c1) - mat(r2, c0) * mat(r1, c1));
}

} // namespace

namespace fuse {

float Mat4::determinant() const noexcept {
    return mData[0][0] * matMinor(*this, 1, 2, 3, 1, 2, 3) -
           mData[0][1] * matMinor(*this, 1, 2, 3, 0, 2, 3) +
           mData[0][2] * matMinor(*this, 1, 2, 3, 0, 1, 3) -
           mData[0][3] * matMinor(*this, 1, 2, 3, 0, 1, 2);
}

Mat4 Mat4::inversed() const noexcept {
    // just define some shorcut
    // NOLINTBEGIN(readability-isolate-declaration)
    const float m00 = mData[0][0], m01 = mData[0][1], m02 = mData[0][2], m03 = mData[0][3];
    const float m10 = mData[1][0], m11 = mData[1][1], m12 = mData[1][2], m13 = mData[1][3];
    const float m20 = mData[2][0], m21 = mData[2][1], m22 = mData[2][2], m23 = mData[2][3];
    const float m30 = mData[3][0], m31 = mData[3][1], m32 = mData[3][2], m33 = mData[3][3];
    // NOLINTEND(readability-isolate-declaration)

    float v0 = m20 * m31 - m21 * m30;
    float v1 = m20 * m32 - m22 * m30;
    float v2 = m20 * m33 - m23 * m30;
    float v3 = m21 * m32 - m22 * m31;
    float v4 = m21 * m33 - m23 * m31;
    float v5 = m22 * m33 - m23 * m32;

    const float t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
    const float t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
    const float t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
    const float t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

    const float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

    const float d00 = t00 * invDet;
    const float d10 = t10 * invDet;
    const float d20 = t20 * invDet;
    const float d30 = t30 * invDet;

    const float d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    const float d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    const float d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    const float d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    v0 = m10 * m31 - m11 * m30;
    v1 = m10 * m32 - m12 * m30;
    v2 = m10 * m33 - m13 * m30;
    v3 = m11 * m32 - m12 * m31;
    v4 = m11 * m33 - m13 * m31;
    v5 = m12 * m33 - m13 * m32;

    const float d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    const float d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    const float d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    const float d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    v0 = m21 * m10 - m20 * m11;
    v1 = m22 * m10 - m20 * m12;
    v2 = m23 * m10 - m20 * m13;
    v3 = m22 * m11 - m21 * m12;
    v4 = m23 * m11 - m21 * m13;
    v5 = m23 * m12 - m22 * m13;

    const float d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    const float d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    const float d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    const float d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    return {d00, d01, d02, d03, d10, d11, d12, d13, d20, d21, d22, d23, d30, d31, d32, d33};
}

// =========================================================
//                      Transform
// =========================================================

Mat4 Mat4::CreateTranslation(const Vec3& translation) noexcept {
    Mat4 mat  = Mat4::kIdentity;
    mat(0, 3) = translation.x;
    mat(1, 3) = translation.y;
    mat(2, 3) = translation.z;
    return mat;
}

Mat4 Mat4::CreateScaling(const Vec3& scale) noexcept {
    Mat4 mat  = Mat4::kIdentity;
    mat(0, 0) = scale.x;
    mat(1, 1) = scale.y;
    mat(2, 2) = scale.z;
    return mat;
}

Mat4 Mat4::CreateRotationX(const Angle& angle) noexcept {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Mat4 rot  = Mat4::kIdentity;
    rot(1, 1) = cos;
    rot(1, 2) = -sin;
    rot(2, 1) = sin;
    rot(2, 2) = cos;
    return rot;
}

Mat4 Mat4::CreateRotationY(const Angle& angle) noexcept {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Mat4 rot  = Mat4::kIdentity;
    rot(0, 0) = cos;
    rot(0, 2) = sin;
    rot(2, 0) = -sin;
    rot(2, 2) = cos;
    return rot;
}

Mat4 Mat4::CreateRotationZ(const Angle& angle) noexcept {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Mat4 rot  = Mat4::kIdentity;
    rot(0, 0) = cos;
    rot(0, 1) = -sin;
    rot(1, 0) = sin;
    rot(1, 1) = cos;
    return rot;
}

Mat4 Mat4::CreateRotation(Angle angle, const Vec3& aaxis) noexcept {
    const float cos         = std::cos(angle);
    const float sin         = std::sin(angle);
    const Vec3  axisNorm    = aaxis.normalized();
    const float oneMinusCos = 1 - cos;
    Mat4        rot         = Mat4::kIdentity;
    // First row
    rot(0, 0) = cos + oneMinusCos * (axisNorm.x * axisNorm.x);
    rot(0, 1) = axisNorm.x * axisNorm.y * oneMinusCos - axisNorm.z * sin;
    rot(0, 2) = axisNorm.x * axisNorm.z * oneMinusCos + axisNorm.y * sin;

    // Second row
    rot(1, 0) = axisNorm.y * axisNorm.x * oneMinusCos + axisNorm.z * sin;
    rot(1, 1) = cos + (axisNorm.y * axisNorm.y) * oneMinusCos;
    rot(1, 2) = axisNorm.y * axisNorm.z * oneMinusCos - axisNorm.x * sin;

    // Third row
    rot(2, 0) = axisNorm.z * axisNorm.x * oneMinusCos - axisNorm.y * sin;
    rot(2, 1) = axisNorm.z * axisNorm.y * oneMinusCos + axisNorm.x * sin;
    rot(2, 2) = cos + (axisNorm.z * axisNorm.z) * oneMinusCos;
    return rot;
}

// ======================================================
//                   View matrix
// ======================================================

Mat4 Mat4::CreateViewLookAt(const Vec3& position,
                            const Vec3& target,
                            const Vec3& upVector) noexcept {
    // View matrix
    //   Rx  Ry  Rz -Tx
    //   Ux  Uy  Uz -Ty
    //  -Dx -Dy -Dz -Tz
    //    0  0   0   1
    //
    // Where:
    //	R => the right vector (x-axis)
    //	U => the up vector (y-axis)
    //	D => the direction vector (z-axis)
    //	T => the translation vector
    //
    const auto zAxis = (target - position).normalized();
    const auto xAxis = zAxis.crossRH(upVector).normalize();
    const auto yAxis = zAxis.crossRH(xAxis).normalize();

    const auto tx = -xAxis.dot(position);
    const auto ty = -yAxis.dot(position);
    const auto tz = zAxis.dot(position);

    Mat4 mat = Mat4::kIdentity;
    // clang-format off
    mat(0, 0) =  xAxis.x; mat(0, 1) =  xAxis.y; mat(0, 2) =  xAxis.z; mat(0, 3) = tx;
    mat(1, 0) =  yAxis.x; mat(1, 1) =  yAxis.y; mat(1, 2) =  yAxis.z; mat(1, 3) = ty;
    mat(2, 0) = -zAxis.x; mat(2, 1) = -zAxis.y; mat(2, 2) = -zAxis.z; mat(2, 3) = tz;
    mat(3, 0) = 0.0f;     mat(3, 1) = 0.0f;     mat(3, 2) = 0.0f;     mat(3, 3) = 1.0f;
    // clang-format on
    return mat;
}

Mat4 Mat4::CreateViewLookTo(const Vec3& position,
                            const Vec3& direction,
                            const Vec3& upVector) noexcept {
    const Vec3 directionNorm = direction.normalized();

    // compute the right vector (view x-axis) from the pUpVector. We need to normalized
    // here because pUpVector is maybe not be a unit vector.
    const auto right = directionNorm.crossRH(upVector).normalized();

    // compute the new up vector (view y-axis) of the view matrix.
    // we can't use the pUpVector here because we need a up vector that is perpandicular to
    // direction and right.
    //
    // Note: direction and right are already normalized, so don't need to normalize up.
    const Vec3 up = right.crossRH(directionNorm);

    // conpute the translation
    const auto tx = -right.dot(position);
    const auto ty = -up.dot(position);
    const auto tz = directionNorm.dot(position);

    // ==============================================================
    // Create the view matrix
    //
    //  Rx  Ry  Rz -Tx
    //  Ux  Uy  Uz -Ty
    // -Dx -Dy -Dz -Tz
    //   0  0   0   1
    //
    // Where:
    //	R => is the right vector (x-axis)
    //	U => is the up vector (y-axis)
    //	D => is the direction vector (z-axis)
    //	T => is the translation vector
    //
    Mat4 matrix;
    // clang-format off
    matrix(0, 0) = right.x;      matrix(0, 1) = right.y;      matrix(0, 2) = right.z;      matrix(0, 3) = tx;
    matrix(1, 0) = up.x;         matrix(1, 1) = up.y;         matrix(1, 2) = up.z;         matrix(1, 3) = ty;
    matrix(2, 0) = -direction.x; matrix(2, 1) = -direction.y; matrix(2, 2) = -direction.z; matrix(2, 3) = tz;
    matrix(3, 0) = 0.0f;         matrix(3, 1) = 0.0f;         matrix(3, 2) = 0.0f;         matrix(3, 3) = 1.0f;
    // clang-format on
    return matrix;
}

// ======================================================
//                  Projection matrix
// ======================================================

Mat4 Mat4::CreateProjectionOrthographic(float width, float height, float near, float far) noexcept {
    return CreateProjectionOrthographicOffCenter(-width * 0.5f,
                                                 width * 0.5f,
                                                 -height * 0.5f,
                                                 height * 0.5f,
                                                 near,
                                                 far);
}

Mat4 Mat4::CreateProjectionOrthographicOffCenter(float left,
                                                 float right,
                                                 float bottom,
                                                 float top,
                                                 float near /* =-1*/,
                                                 float far /*= 1*/) noexcept {
    // ============================================================
    //  P = A(ATA)−1AT
    //  The projection matrix will be defined as fallow
    //
    //  A  0  0  tx
    //  0  B  0  ty
    //  0  0  C  tz
    //  0  0  0  1
    //
    // Where:
    //  A=>     2 / ( right - left )
    //  B=>     2 / ( top - bottom )
    //  C=>   - 2 / ( far - near )
    //  tx=>  -(right + left) / (right - left)
    //  ty=>  -(top + bottom) / (top - bottom)
    //  tz=>  -(far + near)   / (far - near)
    //
    // ============================================================

    const float width  = (right - left);
    const float height = (top - bottom);
    const float depth  = (far - near);

    const float invWidth  = 1.0f / width;
    const float invHeight = 1.0f / height;
    const float invDepth  = 1.0f / depth;

    // compute the translation
    const float tx = -(right + left) * invWidth;
    const float ty = -(top + bottom) * invHeight;
    const float tz = -(far + near) * invDepth;

    Mat4 mat;

    mat(0, 0) = 2.0f * invWidth;
    mat(0, 1) = 0.0f;
    mat(0, 2) = 0.0f;
    mat(0, 3) = tx;

    mat(1, 0) = 0.0f;
    mat(1, 1) = 2.0f * invHeight;
    mat(1, 2) = 0.0f;
    mat(1, 3) = ty;

    mat(2, 0) = 0.0f;
    mat(2, 1) = 0.0f;
    mat(2, 2) = -2.0f * invDepth;
    mat(2, 3) = tz;

    mat(3, 0) = 0.0f;
    mat(3, 1) = 0.0f;
    mat(3, 2) = 0.0f;
    mat(3, 3) = 1.0f;
    return mat;
}

Mat4 Mat4::CreateProjectionPerspectiveOffCenter(
  float left, float right, float bottom, float top, float zNear, float zFar) noexcept {
    // ============================================================
    //
    //  The projection matrix will be defined as fallow
    //
    //  A  0  B  0
    //  0  C  D  0
    //  0  0  E  F
    //  0  0 -1  0
    //
    // Where:
    //  A =>   (2 * near) / (right - left)
    //  B =>   (right + left) / (right - left)
    //  C =>   (2 * near) / ( top - bottom )
    //  D =>   (top + bottom) / (top - bottom)
    //  E =>  -(far + near) / (far - near)
    //  F =>  -( 2 * far * near) / (far - near)
    // ============================================================

    assert(zNear > 0);
    assert(zFar > 0);
    assert(zNear != 0);

    const float width     = right - left;
    const float height    = top - bottom;
    const float depth     = zFar - zNear;
    const float invWidth  = 1.0f / width;
    const float invHeight = 1.0f / height;
    const float invDepth  = 1.0f / depth;

    const float a = 2.0f * zNear * invWidth;
    const float b = (right + left) * invWidth;
    const float c = 2.0f * zNear * invHeight;
    const float d = (top + bottom) * invHeight;
    const float e = -(zFar + zNear) * invDepth;
    const float f = -2.0f * zFar * zNear * invDepth;

    Mat4 matrix = Mat4::kIdentity;
    // clang-format off
    matrix(0, 0) = a;    matrix(0, 1) = 0.0f; matrix(0, 2) =  b;   matrix(0, 3) = 0.0f;
    matrix(1, 0) = 0.0f; matrix(1, 1) = c;    matrix(1, 2) =  d;   matrix(1, 3) = 0.0f;
    matrix(2, 0) = 0.0f; matrix(2, 1) = 0.0f; matrix(2, 2) =  e;   matrix(2, 3) = f;
    matrix(3, 0) = 0.0f; matrix(3, 1) = 0.0f; matrix(3, 2) = -1.f; matrix(3, 3) = 0.0f;
    // clang-format on
    return matrix;
}

Mat4 Mat4::CreateProjectionPerspectiveFOVX(const Angle& fovx,
                                           float        aspectRatio,
                                           float        zNear,
                                           float        zFar) {
    // =====================================
    // Frustum view from top
    //
    //       \     w              /
    //        \---------         /
    //         \       |        /
    //          \      |       /
    //           \     | n    /
    //            \    |     /
    //             \   |    /
    //              \ a|   /
    //               \ |  /
    //                \| /
    //                 \/
    //  Where:
    //      w => half width of the near plane
    //      n => distance of the near plane
    //      a => half fov x
    //
    // By definition tan(x) = opposite / adjancent
    //  tan(a) = w / n => w = n * tan(a)
    //
    // =====================================
    const float nearHalfWidth  = zNear * std::tan(0.5f * fovx);
    const float nearHalfHeight = nearHalfWidth / aspectRatio;
    return CreateProjectionPerspectiveOffCenter(-nearHalfWidth,
                                                nearHalfWidth,
                                                -nearHalfHeight,
                                                nearHalfHeight,
                                                zNear,
                                                zFar);
}

Mat4 Mat4::CreateProjectionPerspectiveFOVY(const Angle& fovY,
                                           float        aspectRatio,
                                           float        zNear,
                                           float        zFar) {
    // =====================================
    //  Frustum view from side
    //
    //          /
    //         / |
    //        /  |
    //       /   |
    //      /    | h
    //     /     |
    //      a--------
    //     \    n
    //      \
    //       \
    //  Where:
    //      h => half height of the near plane
    //      n => distance of the near plane
    //      a => half fov y
    //
    // By definition tan(x) = opposite / adjancent so,
    //  tan(a) = h / n => h = n * tan(a)
    // =====================================
    const float nearHalfHeight = zNear * std::tan(fovY * 0.5f);
    const float nearHalfWidth  = nearHalfHeight * aspectRatio;
    return CreateProjectionPerspectiveOffCenter(-nearHalfWidth,
                                                nearHalfWidth,
                                                -nearHalfHeight,
                                                nearHalfHeight,
                                                zNear,
                                                zFar);
}

} // namespace  fuse
