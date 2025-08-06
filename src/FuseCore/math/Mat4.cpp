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


} // namespace  fuse
