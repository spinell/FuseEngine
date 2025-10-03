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

/// @brief Camera component
struct CCamera {
    Angle fovy      = degrees(60.f); //< Vertical field of view.
    float nearPlane = 0.1f;          //< Near plane distance.
    float farPlane  = 1000.f;        //< Far plane distance.
    float aspect    = 16.f / 9.f;    //< Aspect ratio (width / height).
    float viewportX = 0.f;           //< Viewport X position in normalize coordinate.
    float viewportY = 0.f;           //< Viewport Y position in normalize coordinate.
    float viewportW = 1.f;           //< Viewport width in normalize coordinate.
    float viewportH = 1.f;           //< Viewport height in normalize coordinate.
    // bool  isMain      = false;         //< Is this the main camera?
    // bool  isActive    = true;          //< Is this camera active?
    // bool  isOrtho     = false;         //< Is this an orthographic camera?
    // float orthoWidth  = 10.f;          //< Ortho width (only used if isOrtho is true).
    // float orthoHeight = 10.f;          //< Ortho height (only used if isOrtho is true).
    float clearColor[4] = {0.2f, 0.2f, 0.5f, 1.f}; //< Clear color for this camera.
};

} // namespace fuse
