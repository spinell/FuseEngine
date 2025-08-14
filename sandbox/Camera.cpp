#include "Camera.h"

fuse::Mat4 Camera::getProjMatrix() const noexcept {
    return fuse::Mat4::CreateProjectionPerspectiveFOVY(mFieldOfView, mAspectRatio, mZNear, mZFar);
}

fuse::Mat4 Camera::getViewMatrix() noexcept {
    //mDirection.x = std::cos(mPitch) * std::cos(mYaw);
    //mDirection.y = std::sin(mPitch);
    //mDirection.z = std::sin(mYaw) * std::cos(mPitch);
    //mDirection.normalize();
    mRight = mDirection.crossRH(fuse::Vec3::kAxisY);
    mUp    = mRight.crossRH(mDirection);
    return fuse::Mat4::CreateViewLookTo(mPosition, mDirection, fuse::Vec3::kAxisY);
}

void Camera::pitch(const fuse::Angle& angle) {
    mPitch += angle;
    if (mPitch > fuse::degrees(89.f)) {
        mPitch = fuse::degrees(89.f);
    }
    if (mPitch < fuse::degrees(-89.f)) {
        mPitch = fuse::degrees(-89.f);
    }
    const auto rot = fuse::Mat4::CreateRotation(angle, mRight);
    const auto d   = rot * fuse::Vec4(mDirection.x, mDirection.y, mDirection.z, 0);
    mDirection     = fuse::Vec3(d.x, d.y, d.z);
}

void Camera::yaw(const fuse::Angle& angle) {
    mYaw += angle;
    const auto rot = fuse::Mat4::CreateRotationY(angle);
    const auto d   = rot * fuse::Vec4(mDirection.x, mDirection.y, mDirection.z, 0);
    const auto r   = rot * fuse::Vec4(mRight.x, mRight.y, mRight.z, 0);
    mDirection     = fuse::Vec3(d.x, d.y, d.z);
    mRight         = fuse::Vec3(r.x, r.y, r.z);
}
