#pragma once
#include "FuseCore/math/Mat4.h"
#include "FuseCore/math/Vec3.h"

class Camera {
public:
    Camera() = default;

    void setAspectRatio(float aspectRatio) noexcept { mAspectRatio = aspectRatio; };

    void setZNear(float zNear) noexcept { mZNear = zNear; };

    void setZFar(float zFar) noexcept { mZFar = zFar; };

    void setPosition(const fuse::Vec3& position) noexcept { mPosition = position; };

    [[nodiscard]] const fuse::Vec3& getRight() const noexcept { return mRight; };
    [[nodiscard]] const fuse::Vec3& getDirection() const noexcept { return mDirection; };
    [[nodiscard]] const fuse::Vec3& getPosition() const noexcept { return mPosition; };

    void setDirection(const fuse::Vec3& direction) noexcept { mDirection = direction; };

    [[nodiscard]] fuse::Mat4 getProjMatrix() const noexcept;
    [[nodiscard]] fuse::Mat4 getViewMatrix() noexcept;

    // rotation around local x-axis
    void pitch(const fuse::Angle& angle);

    // rotation around local y-axis
    void yaw(const fuse::Angle& angle);

private:
    fuse::Vec3 mPosition{fuse::Vec3::kZero};
    fuse::Vec3 mDirection{fuse::Vec3::kAxisZNeg};
    fuse::Vec3 mRight{fuse::Vec3::kAxisX};
    fuse::Vec3 mUp{fuse::Vec3::kAxisY};

    fuse::Angle mYaw{fuse::degrees(-90.0f)};
    fuse::Angle mPitch{};
    fuse::Angle mFieldOfView{fuse::degrees(45.0f)};
    float       mAspectRatio{4.f / 3.f};
    float       mZNear{0.1f};
    float       mZFar{1000.f};
};
