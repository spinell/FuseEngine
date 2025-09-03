#pragma once
#include "Camera.h"
#include "FuseApp/Application.h"

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
    unsigned int mVertexShader   = 0;
    unsigned int mFragmentShader = 0;
    unsigned int mShaderProgram  = 0;
    unsigned int mVao            = 0;
    unsigned int mVbo            = 0;
    Camera       mCamera;
};
