#pragma once

#include "FuseApp/Application.h"

#include <memory>

namespace fuse {
class Scene;
class SceneHierarchyPanel;
class InspectorPanel;
class LogPanel;
class ScenePanel;

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

    std::unique_ptr<Scene>               mScene;
    std::unique_ptr<SceneHierarchyPanel> mSceneHierarchyPanel;
    std::unique_ptr<InspectorPanel>      mInspectorPanel;
    std::unique_ptr<LogPanel>            mLogPanel;
    std::unique_ptr<ScenePanel>          mScenePanel;
};

} // namespace fuse
