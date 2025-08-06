#pragma once
#include <ostream>

namespace fuse {
class Vec4;

// teach gtest how to print Vec4
void PrintTo(const Vec4& v, std::ostream* os);

} // namespace fuse
