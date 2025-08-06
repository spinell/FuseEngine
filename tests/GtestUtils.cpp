#include "GtestUtils.h"

#include <FuseCore/math/Vec4.h>

#include <format>

namespace fuse {

// teach gtest how to print Vec4
void PrintTo(const Vec4& v, std::ostream* os) {
    const auto str = std::format("[{}, {}, {}, {}]", v.x, v.y, v.z, v.w);
    *os << str;
}

} // namespace fuse
