#pragma once
#include "Camera.h"
#include "FuseApp/Application.h"

#include <FuseApp/SceneRenderer.h>
#include <FuseCore/scene/Scene.h>

#include <memory>

/// @brief Base class for fuse application.
class Application : public fuse::Application {
public:
    /// @brief
    Application();

    /// @brief
    ~Application() override;

    Application(const Application&)             = delete;
    Application(const Application&&)            = delete;
    Application& operator=(const Application&)  = delete;
    Application& operator=(const Application&&) = delete;

    bool onInit() override;
    void onShutdown() override;
    void onUpdate(float deltaTime) override;
    void onEvent(const fuse::Event& event) override;
    void onImGui() override;

private:
    std::unique_ptr<fuse::SceneRenderer> mSceneRenderer;
    Camera                               mCamera;
    fuse::Scene                          mScene;
};
