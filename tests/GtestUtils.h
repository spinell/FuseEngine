#pragma once
#include <ostream>

namespace fuse {
class Angle;
class Vec4;

// teach gtest how to print data
void PrintTo(const Angle& a, std::ostream* os);
void PrintTo(const Vec4& v, std::ostream* os);

} // namespace fuse
