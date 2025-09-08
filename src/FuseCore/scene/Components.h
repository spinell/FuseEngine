#pragma once
#include <FuseCore/math/Angle.h>
#include <FuseCore/math/Vec3.h>
#include <FuseCore/math/Vec4.h>

namespace fuse {

struct CTransform {
    Vec3 position = {0.f, 0.f, 0.f};
    Vec3 rotation = {0.f, 0.f, 0.f};
    Vec3 scale    = {1.f, 1.f, 1.f};
};

static_assert(sizeof(CTransform) == sizeof(float) * 9);

struct CRotator {
    Angle angle;
    Vec3  axis{}; // TODO: should be init....
};

static_assert(sizeof(CRotator) == sizeof(float) * 4);

struct CTranslator {
    Vec3  direction; // TODO: should be init....
    float duration;  // in second
};

static_assert(sizeof(CTranslator) == sizeof(float) * 4);

struct CMesh {
    Vec4 color;
};

} // namespace fuse
