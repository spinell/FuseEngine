#include "SandboxApplication.h"

#include "PlayerScript.h"

#include <FuseApp/ImGui/Widget.h>
#include <FuseApp/TransformerSystem.h>
#include <FuseCore/Input.h>
#include <FuseCore/scene/components/CNativeScript.h>
#include <FuseCore/scene/components/Components.h>
#include <FuseCore/scene/NativeScriptSystem.h>

#include <imgui.h>
#include <spdlog/spdlog.h>

namespace {

float windowWidth  = 0;
float windowHeight = 0;
fuse::Entity playerEntity;
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

    auto floorEntity = mScene.createEntity("Floor");
    floorEntity.addComponent<fuse::CTransform>();
    floorEntity.getComponent<fuse::CTransform>().translation = {0.f, -1.0f, 0.f};
    floorEntity.getComponent<fuse::CTransform>().scale = {50.f, 1.0f, 50.f};
    auto& floorMesh = floorEntity.addComponent<fuse::CMesh>();
    floorMesh.color = {0.3f, 0.3f, 0.3f, 1.0f};

    auto  e = createCube(mScene, {0, 2, -11});
    auto& r = e.addComponent<fuse::CRotator>();
    r.angle = fuse::degrees(10);

    createCube(mScene, {-11, 2, -11});

    playerEntity = mScene.createEntity("Player");
    playerEntity.addComponent<fuse::CTransform>().translation = {0, 0, 5};
    playerEntity.addComponent<fuse::CCamera>();
    playerEntity.addComponent<fuse::CNativeScript>(new PlayerScript());



    mSceneRenderer = std::make_unique<fuse::SceneRenderer>();
    return true;
}

void Application::onShutdown() { mSceneRenderer.reset(); }

void Application::onUpdate(float deltaTime) {
    fuse::TransformerSystem  transformerSystem;
    fuse::NativeScriptSystem nativeScriptSystem;

    const auto&      ccamera         = playerEntity.getComponent<fuse::CCamera>();
    const fuse::Mat4 proj            = fuse::Mat4::CreateProjectionPerspectiveFOVY(ccamera.fovy,
                                                                        ccamera.aspect,
                                                                        ccamera.nearPlane,
                                                                        ccamera.farPlane);
    const auto&      playerTransform = playerEntity.getComponent<fuse::CTransform>();
    const fuse::Mat4 view =
      fuse::Mat4::CreateRotationX(fuse::degrees(playerTransform.rotation.x)) *
      fuse::Mat4::CreateRotationY(fuse::degrees(playerTransform.rotation.y)) *
      fuse::Mat4::CreateTranslation(playerEntity.getComponent<fuse::CTransform>().translation);
    transformerSystem.update(mScene, deltaTime);
    nativeScriptSystem.update(deltaTime, mScene.getRegistry(), &mScene);

    glClearColor(ccamera.clearColor[0], ccamera.clearColor[1], ccamera.clearColor[2], ccamera.clearColor[3]);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, windowWidth * ccamera.viewportW, windowHeight * ccamera.viewportH);
    mSceneRenderer->renderScene(mScene, proj, view.inversed());


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
}

void Application::onEvent(const fuse::Event& event) {
    fuse::Application::onEvent(event);

    if (const auto* resizedEvent = event.getIf<fuse::WindowResizedEvent>()) {
        windowWidth = resizedEvent->getWidth();
        windowHeight = resizedEvent->getHeight();
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
