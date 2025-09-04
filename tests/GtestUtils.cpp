#include "GtestUtils.h"

#include <FuseCore/math/Angle.h>
#include <FuseCore/math/Mat4.h>
#include <FuseCore/math/Vec4.h>

#include <format>

namespace fuse {

void PrintTo(const Angle& a, std::ostream* os) {
    const auto str = std::format("degrees={}, radian={}", a.asDegrees(), a.asRadians());
    *os << str;
}

void PrintTo(const Mat4& m, std::ostream* os) {
    // TODO: implement std::format for vec4
    const auto r0    = m.getRow(0);
    const auto r1    = m.getRow(1);
    const auto r2    = m.getRow(2);
    const auto r3    = m.getRow(3);
    const auto r0Str = std::format("{}, {}, {}, {}", r0.x, r0.y, r0.z, r0.w);
    const auto r1Str = std::format("{}, {}, {}, {}", r1.x, r1.y, r1.z, r1.w);
    const auto r2Str = std::format("{}, {}, {}, {}", r2.x, r2.y, r2.z, r2.w);
    const auto r3Str = std::format("{}, {}, {}, {}", r3.x, r3.y, r3.z, r3.w);
    const auto str =
      std::format("row0 = [{}] row1 = [{}] row2 = [{}] row3 = [{}]", r0Str, r1Str, r2Str, r3Str);
    *os << str;
}

void PrintTo(const Vec4& v, std::ostream* os) {
    const auto str = std::format("[{}, {}, {}, {}]", v.x, v.y, v.z, v.w);
    *os << str;
}

} // namespace fuse
