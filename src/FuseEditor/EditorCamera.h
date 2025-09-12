#pragma once
#include <FuseCore/math/Mat4.h>
#include <FuseCore/math/Vec3.h>

namespace fuse {

/// @brief
class EditorCamera {
public:
    EditorCamera() = default;

    void setAspectRatio(float aspectRatio) noexcept { mAspectRatio = aspectRatio; }

    void setZNear(float zNear) noexcept { mZNear = zNear; }

    void setZFar(float zFar) noexcept { mZFar = zFar; }

    void setPosition(const Vec3& position) noexcept { mPosition = position; }

    [[nodiscard]] const Vec3& getRight() const noexcept { return mRight; }

    [[nodiscard]] const Vec3& getDirection() const noexcept { return mDirection; }

    [[nodiscard]] const Vec3& getPosition() const noexcept { return mPosition; }

    void setDirection(const Vec3& direction) noexcept { mDirection = direction; }

    [[nodiscard]] Mat4 getProjMatrix() const noexcept;
    [[nodiscard]] Mat4 getViewMatrix() noexcept;

    // rotation around local x-axis
    void pitch(const Angle& angle);

    // rotation around local y-axis
    void yaw(const Angle& angle);

    void update(float deltaTime);

private:
    Vec3 mPosition{Vec3::kZero};
    Vec3 mDirection{Vec3::kAxisZNeg};
    Vec3 mRight{Vec3::kAxisX};
    Vec3 mUp{Vec3::kAxisY};

    Angle mYaw{degrees(-90.0f)};
    Angle mPitch;
    Angle mFieldOfView{degrees(45.0f)};
    float mAspectRatio{4.f / 3.f};
    float mZNear{0.1f};
    float mZFar{1000.f};

    float mMovementSpeed = 50.0f;
};

} // namespace fuse
