#include "PlayerScript.h"

#include <FuseCore/Input.h>
#include <FuseCore/scene/components/Components.h>

#include <spdlog/spdlog.h>

void PlayerScript::onCreate() { spdlog::info("TestScriptComponent::onCreate"); }

void PlayerScript::onUpdate(float elapsed) {
    const float speed = 5.0f * elapsed;
    auto& transform = mRegistry->get<fuse::CTransform>(mEntity);

    // Make each pixel correspond to a 1/8 of a degree.
    const auto [x, y] = fuse::Input::GetMousePositionDelta();
    const auto dx = x * fuse::degrees(0.125f);
    const auto dy = y * fuse::degrees(0.125f);
    transform.rotation.y +=  -dx.asDegrees();// rotation around local Up
    transform.rotation.x +=  -dy.asDegrees();// rotation around local right

    if (fuse::Input::IsKeyDown(fuse::ScanCode::A)) {
        transform.translation.x -= speed;
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::D)) {
        transform.translation.x += speed;
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::W)) {
        transform.translation.z -= speed;
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::S)) {
        transform.translation.z += speed;
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::Q)) {
        transform.translation.y -= speed;
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::E)) {
        transform.translation.y += speed;
    }
}

void PlayerScript::onLastUpdate(float /*elapsed*/) {}

void PlayerScript::onDestroy() { spdlog::info("TestScriptComponent::onDestroy"); }
