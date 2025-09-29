#include "EditorCamera.h"

#include <imgui.h>

namespace fuse {


void EditorCamera::update(float deltaTime) {
    if (ImGui::GetIO().WantCaptureMouse) {
        //return;
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
        ImGui::SetWindowFocus(nullptr);

        // Make each pixel correspond to a 1/8 of a degree.
        const auto [mouseX, mouseY] = ImGui::GetIO().MouseDelta;
        const auto dx               = fuse::degrees(0.125f) * mouseX; // rotation around local Up
        const auto dy               = fuse::degrees(0.125f) * mouseY; // rotation around local right
        pitch(-dy);
        yaw(-dx);

        auto pos = getPosition();
        // move forward
        if (ImGui::IsKeyDown(ImGuiKey_W)) {
            pos += getDirection() * mMovementSpeed * deltaTime;
        }
        // move backward
        if (ImGui::IsKeyDown(ImGuiKey_S)) {
            pos -= getDirection() * mMovementSpeed * deltaTime;
        }
        // move left
        if (ImGui::IsKeyDown(ImGuiKey_A)) {
            pos -= getRight() * mMovementSpeed * deltaTime;
        }
        // move right
        if (ImGui::IsKeyDown(ImGuiKey_D)) {
            pos += getRight() * mMovementSpeed * deltaTime;
        }
        // move up
        if (ImGui::IsKeyDown(ImGuiKey_Q)) {
            pos += fuse::Vec3::kAxisY * mMovementSpeed * deltaTime;
        }
        // move down
        if (ImGui::IsKeyDown(ImGuiKey_E)) {
            pos += fuse::Vec3::kAxisYNeg * mMovementSpeed * deltaTime;
        }
        setPosition(pos);
    }
}

Mat4 EditorCamera::getProjMatrix() const noexcept {
    return Mat4::CreateProjectionPerspectiveFOVY(mFieldOfView, mAspectRatio, mZNear, mZFar);
}

Mat4 EditorCamera::getViewMatrix() noexcept {
    //mDirection.x = std::cos(mPitch) * std::cos(mYaw);
    //mDirection.y = std::sin(mPitch);
    //mDirection.z = std::sin(mYaw) * std::cos(mPitch);
    //mDirection.normalize();
    mRight = mDirection.crossRH(Vec3::kAxisY);
    mUp    = mRight.crossRH(mDirection);
    return Mat4::CreateViewLookTo(mPosition, mDirection, Vec3::kAxisY);
}

void EditorCamera::pitch(const Angle& angle) {
    mPitch += angle;
    if (mPitch > degrees(89.f)) {
        mPitch = degrees(89.f);
    }
    if (mPitch < degrees(-89.f)) {
        mPitch = degrees(-89.f);
    }
    const auto rot = Mat4::CreateRotation(angle, mRight);
    const auto d   = rot * Vec4(mDirection.x, mDirection.y, mDirection.z, 0);
    mDirection     = Vec3(d.x, d.y, d.z);
}

void EditorCamera::yaw(const Angle& angle) {
    mYaw += angle;
    const auto rot = Mat4::CreateRotationY(angle);
    const auto d   = rot * Vec4(mDirection.x, mDirection.y, mDirection.z, 0);
    const auto r   = rot * Vec4(mRight.x, mRight.y, mRight.z, 0);
    mDirection     = Vec3(d.x, d.y, d.z);
    mRight         = Vec3(r.x, r.y, r.z);
}


} // namespace fuse
