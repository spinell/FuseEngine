#pragma once

#include "FuseApp/Application.h"
#include "FuseApp/SceneRenderer.h"

#include <memory>

namespace fuse {
class Scene;
class SceneHierachyPanel;
class InspectorPanel;

class EditorApplication : public fuse::Application {
public:
    EditorApplication();
    ~EditorApplication() override;

    EditorApplication(const EditorApplication&)             = delete;
    EditorApplication(const EditorApplication&&)            = delete;
    EditorApplication& operator=(const EditorApplication&)  = delete;
    EditorApplication& operator=(const EditorApplication&&) = delete;

private:
    void onUpdate(float /*deltaTime*/) override;
    void onEvent(const Event& event) override;
    void onImGui() override;
    bool onInit() override;
    void onShutdown() override;

    void imguiDrawMainMenuBar();

    std::unique_ptr<Scene>              mScene;
    std::unique_ptr<SceneHierachyPanel> mSceneHierachyPanel;
    std::unique_ptr<InspectorPanel>     mInspectorPanel;
    std::unique_ptr<SceneRenderer>      mSceneRenderer;
};

} // namespace fuse
