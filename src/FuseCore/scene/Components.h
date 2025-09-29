#pragma once
#include <FuseCore/math/Angle.h>
#include <FuseCore/math/Vec3.h>
#include <FuseCore/math/Vec4.h>

#include <string>

namespace fuse {

struct NameComponent {
    std::string name;

    auto operator<=>(const NameComponent&) const = default;
};

struct IDComponent {
    IDComponent() {
        static unsigned staticId = 0;
        id                       = staticId++;
    }

    auto operator<=>(const IDComponent&) const = default;

    unsigned id;
};

struct CTransform {
    Vec3 translation = {0.f, 0.f, 0.f};
    Vec3 rotation    = {0.f, 0.f, 0.f};
    Vec3 scale       = {1.f, 1.f, 1.f};
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
    Vec4 color{1.f, 1.f, 1.f, 1.f};
};

} // namespace fuse
