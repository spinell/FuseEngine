#include "Application.h"

#include <FuseApp/ImGui/Widget.h>
#include <FuseApp/TransformerSystem.h>
#include <FuseCore/Input.h>
#include <FuseCore/scene/Components.h>

#include <imgui.h>
#include <spdlog/spdlog.h>

namespace {

fuse::Entity entityToDestroy;

fuse::Entity createCube(fuse::Scene&      scene,
                        const fuse::Vec3& position,
                        const fuse::Vec4& color = fuse::Vec4{1.f, 1.f, 1.f, 1.f}) {
    fuse::Entity entity = scene.createEntity();

    auto& transform       = entity.addComponent<fuse::CTransform>();
    transform.translation = position;

    auto& mesh = entity.addComponent<fuse::CMesh>();
    mesh.color = color;

    return entity;
}


} // namespace

Application::Application() = default;

Application::~Application() = default;

bool Application::onInit() {
    auto  e = createCube(mScene, {0, 0, -11});
    auto& r = e.addComponent<fuse::CRotator>();
    r.angle = fuse::degrees(10);

    createCube(mScene, {-11, 10, -11});
    mSceneRenderer = std::make_unique<fuse::SceneRenderer>();
    return true;
}

void Application::onShutdown() { mSceneRenderer.reset(); }

void Application::onUpdate(float deltaTime) {
    glClearColor(1.0f, .0f, 1.f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fuse::TransformerSystem transformerSystem;

    const fuse::Mat4 proj = mCamera.getProjMatrix();
    const fuse::Mat4 view = mCamera.getViewMatrix();
    transformerSystem.update(mScene, deltaTime);
    mSceneRenderer->renderScene(mScene, proj, view);

    if (fuse::Input::IsKeyDown(fuse::ScanCode::A)) {
        auto pos = mCamera.getPosition();
        pos -= mCamera.getRight() * 2;
        mCamera.setPosition(pos);
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::D)) {
        auto pos = mCamera.getPosition();
        pos += mCamera.getRight() * 2;
        mCamera.setPosition(pos);
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::W)) {
        auto pos = mCamera.getPosition();
        pos += mCamera.getDirection() * 2;
        mCamera.setPosition(pos);
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::S)) {
        auto pos = mCamera.getPosition();
        pos -= mCamera.getDirection() * 2;
        mCamera.setPosition(pos);
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::Q)) {
        auto pos = mCamera.getPosition();
        pos += fuse::Vec3::kAxisY;
        mCamera.setPosition(pos);
    }
    if (fuse::Input::IsKeyDown(fuse::ScanCode::E)) {
        auto pos = mCamera.getPosition();
        pos += fuse::Vec3::kAxisYNeg;
        mCamera.setPosition(pos);
    }
    if (fuse::Input::IsKeyPressed(fuse::ScanCode::Z)) {
        entityToDestroy                                   = createCube(mScene, {0, 0, 0});
        entityToDestroy.getComponent<fuse::CMesh>().color = {0.5f, 0.5f, 0.5f, 1.0f};
        entityToDestroy.addComponent<fuse::CTranslator>(fuse::Vec3{1, 0, 0}, 2.0f);
    }
    if (fuse::Input::IsKeyPressed(fuse::ScanCode::X)) {
        if (entityToDestroy.isValid()) {
            entityToDestroy.destroy();
        }
    }
    if (fuse::Input::IsKeyPressed(fuse::ScanCode::C)) {
        auto newEnt = mScene.duplicateEntity(entityToDestroy);
        newEnt.getOrAddComponent<fuse::CTranslator>(fuse::Vec3{0, 1, 0}, 2.0f);
    }

    const auto [x, y] = fuse::Input::GetMousePositionDelta();
    // Make each pixel correspond to a 1/8 of a degree.
    const auto dx = x * fuse::degrees(0.125f);
    const auto dy = y * fuse::degrees(0.125f);
    mCamera.pitch(-dy); // rotation around local Up
    mCamera.yaw(-dx);   // rotation around local right
}

void Application::onEvent(const fuse::Event& event) {
    fuse::Application::onEvent(event);

    if (const auto* resizedEvent = event.getIf<fuse::WindowResizedEvent>()) {
        glViewport(0, 0, resizedEvent->getWidth(), resizedEvent->getHeight());
        mCamera.setAspectRatio(static_cast<float>(resizedEvent->getWidth()) /
                               static_cast<float>(resizedEvent->getHeight()));
    }
}

void Application::onImGui() {
    ImGui::ShowDemoWindow();

    if (ImGui::Begin("Entities")) {
        for (auto entity : mScene.getRegistry().view<entt::entity>()) {

            fuse::ImGuiTextFmt("{} id={}",
                               mScene.getRegistry().get<fuse::NameComponent>(entity).name.c_str(),
                               mScene.getRegistry().get<fuse::IDComponent>(entity).id);

            if (mScene.getRegistry().try_get<fuse::CTranslator>(entity)) {
                ImGui::TextUnformatted("Translator");
            }
        }
    }
    ImGui::End();
}
