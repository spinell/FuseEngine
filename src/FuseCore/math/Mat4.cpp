#include "Mat4.h"

#include <cmath>

namespace {

inline float matMinor(const fuse::Mat4& mat, int r0, int r1, int r2, int c0, int c1, int c2) {
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

// =========================================================
//                      Transform
// =========================================================

Mat4 Mat4::CreateTranslation(float x, float y, float z) noexcept {
    Mat4 mat  = Mat4::kIdentity;
    mat(0, 3) = x;
    mat(1, 3) = y;
    mat(2, 3) = z;
    return mat;
}

Mat4 Mat4::CreateScaling(float x, float y, float z) noexcept {
    Mat4 mat  = Mat4::kIdentity;
    mat(0, 0) = x;
    mat(1, 1) = y;
    mat(2, 2) = z;
    return mat;
}

Mat4 Mat4::CreateRotationX(float angle) noexcept {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Mat4 rot  = Mat4::kIdentity;
    rot(1, 1) = cos;
    rot(1, 2) = -sin;
    rot(2, 1) = sin;
    rot(2, 2) = cos;
    return rot;
}

Mat4 Mat4::CreateRotationY(float angle) noexcept {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Mat4 rot  = Mat4::kIdentity;
    rot(0, 0) = cos;
    rot(0, 2) = sin;
    rot(2, 0) = -sin;
    rot(2, 2) = cos;
    return rot;
}

Mat4 Mat4::CreateRotationZ(float angle) noexcept {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Mat4 rot  = Mat4::kIdentity;
    rot(0, 0) = cos;
    rot(0, 1) = -sin;
    rot(1, 0) = sin;
    rot(1, 1) = cos;
    return rot;
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
    //
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

    Mat4 matrix  = Mat4::kIdentity;
    matrix(0, 0) = 2.0f * zNear * invWidth;
    matrix(0, 2) = (right + left) * invWidth;

    matrix(1, 1) = 2.0f * zNear * invHeight;
    matrix(1, 2) = (top + bottom) * invHeight;

    matrix(2, 2) = -(zFar + zNear) * invDepth;
    matrix(2, 3) = -2.0f * zFar * zNear * invDepth;

    matrix(3, 2) = -1.0f;
    matrix(3, 3) = 0.0f;
    return matrix;
}

Mat4 Mat4::CreateProjectionPerspectiveFOVX(float fovx, float aspectRatio, float zNear, float zFar) {
    // =====================================
    //
    //          Frustum view from top
    //
    //     \                        /
    //      \                      /
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
    //
    //  Where:
    //      w => half width of the near plane
    //      n => distance of the near plane
    //      a => half fov x
    //
    // By definition tan(x) = opposite / adjancent so,
    //
    // tan(a) = w / n    =>    w = n * tan(a)
    //
    //
    // =====================================

    // compute the near plane half width
    const float nearHalfWidth = zNear * std::tan(0.5f * fovx);

    // compute the near plane half height with the aspect ratio
    //
    // aspect ratio = width / height
    //
    // so divided the near plane half width by the aspect ration will
    // give us the near plane half height that match the aspect ratio
    const float nearHalfHeight = nearHalfWidth / aspectRatio;

    return CreateProjectionPerspectiveOffCenter(-nearHalfWidth,
                                                nearHalfWidth,
                                                -nearHalfHeight,
                                                nearHalfHeight,
                                                zNear,
                                                zFar);
}

Mat4 Mat4::CreateProjectionPerspectiveFOVY(float fovY, float aspectRatio, float zNear, float zFar) {
    // =====================================
    //  Frustum view from side
    //
    //            /
    //           /
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
    //
    // tan(a) = h / n    =>    h = n * tan(a)
    // =====================================
    const auto fovy     = fovY;
    const auto halfFovy = fovy * 0.5f;

    // compute the near plane half height
    const float nearHalfHeight = zNear * std::tan(halfFovy);

    // compute the near plane half width with the aspect ratio
    //
    // aspect ratio = width / height
    //
    // so mutiply the near plane half height by the aspect ration will
    // give us the near plane half width that match the aspect ratio
    const float nearHalfWidth = nearHalfHeight * aspectRatio;

    return CreateProjectionPerspectiveOffCenter(-nearHalfWidth,
                                                nearHalfWidth,
                                                -nearHalfHeight,
                                                nearHalfHeight,
                                                zNear,
                                                zFar);
}

} // namespace  fuse
