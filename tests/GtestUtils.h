#pragma once
#include <ostream>

namespace fuse {
class Angle;
class Mat4;
class Vec4;

// teach gtest how to print data
void PrintTo(const Angle& a, std::ostream* os);
void PrintTo(const Mat4& m, std::ostream* os);
void PrintTo(const Vec4& v, std::ostream* os);

} // namespace fuse
