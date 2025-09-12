#pragma once

#include "FuseApp/Application.h"

namespace fuse {
class Scene;
class SceneHierachyPanel;

class EditorApplication : public fuse::Application {
public:
    EditorApplication();
    ~EditorApplication() override;

private:
    void onUpdate(float /*deltaTime*/) override;
    void onEvent(const Event& event) override;
    void onImGui() override;
    bool onInit() override;
    void onShutdown() override;

    void imguiDrawMainMenuBar();

    Scene* mScene{};
    SceneHierachyPanel* mSceneHierachyPanel{};
};

} // namespace fuse
