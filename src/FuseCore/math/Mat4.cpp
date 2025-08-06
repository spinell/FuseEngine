#include "Mat4.h"

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

} // namespace  fuse
