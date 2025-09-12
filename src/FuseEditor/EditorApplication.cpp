#include "EditorApplication.h"

#include "FuseCore/scene/Components.h"
#include "FuseCore/scene/Scene.h"
#include "panel/InspectorPanel.h"
#include "panel/SceneHierachyPanel.h"

#include <imgui.h>

namespace {
bool showDemoWindow        = false;
bool showMetricsWindow     = false;
bool showDebugLogWindow    = false;
bool showIDStackToolWindow = false;
} // namespace

namespace fuse {

EditorApplication::EditorApplication() {
    mScene              = std::make_unique<Scene>();
    mSceneHierarchyPanel = std::make_unique<SceneHierarchyPanel>();
    mInspectorPanel     = std::make_unique<InspectorPanel>();

    mEditorCamera.setPosition({0, 0, 10});
    {
        auto e = mScene->createEntity("Floor");
        e.addComponent<CTransform>(Vec3{0, -10, 0}, Vec3{0, 0, 0}, Vec3{100, 0, 100});
        e.addComponent<CMesh>(Vec4{0.5f, 0.5f, 0.5f, 1.f});
    }
    {
        auto e = mScene->createEntity("Cube");
        e.addComponent<CTransform>(Vec3{0, 0, 0}, Vec3{0, 45, 0}, Vec3{1, 1, 1});
        e.addComponent<CMesh>(Vec4{1.f, 1.f, 1.f, 1.f});
    }
}

EditorApplication::~EditorApplication() = default;

void EditorApplication::onUpdate(float deltaTime) {
    // TODO: clear should go in base class
    glClearColor(1.0f, .2f, .2f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mEditorCamera.update(deltaTime);

    const auto proj = mEditorCamera.getProjMatrix();
    const auto view = mEditorCamera.getViewMatrix();
    mSceneRenderer->renderScene(*mScene, proj, view);
}

void EditorApplication::onEvent(const Event& event) {
    if (const auto* e = event.getIf<WindowResizedEvent>()) {
        glViewport(0, 0, e->getWidth(), e->getHeight());
        mEditorCamera.setAspectRatio(static_cast<float>(e->getWidth()) /
                                     static_cast<float>(e->getHeight()));
    }
}

void EditorApplication::onImGui() {
    imguiDrawMainMenuBar();

    if (showDemoWindow) {
        ImGui::ShowDemoWindow(&showDemoWindow);
    }
    if (showMetricsWindow) {
        ImGui::ShowMetricsWindow(&showMetricsWindow);
    }
    if (showDebugLogWindow) {
        ImGui::ShowDebugLogWindow(&showDebugLogWindow);
    }
    if (showIDStackToolWindow) {
        ImGui::ShowIDStackToolWindow(&showIDStackToolWindow);
    }

    mSceneHierarchyPanel->onImGui();
    mInspectorPanel->onImGui();
}

bool EditorApplication::onInit() {
    mSceneHierarchyPanel->setScene(mScene.get());
    mSceneHierarchyPanel->setSelectionCallback(
      [&](Entity entity) { mInspectorPanel->setEntity(entity); });


    mSceneRenderer = std::make_unique<SceneRenderer>();

    return true;
}

void EditorApplication::onShutdown() { mSceneRenderer.reset(); }

void EditorApplication::imguiDrawMainMenuBar() {
    const bool isMainMenuBarVisible = ImGui::BeginMainMenuBar();
    if (!isMainMenuBarVisible) {
        return;
    }

    //
    // File menu
    //
    if (ImGui::BeginMenu("File", true /*enabled*/)) {
        if (ImGui::MenuItem("New Scene", "Ctrl+N", nullptr, false)) {
        }
        if (ImGui::MenuItem("Open Scene", "Ctrl+O", nullptr, false)) {
        }
        if (ImGui::MenuItem("Save Scene", "Ctrl+S", nullptr, false)) {
        }
        if (ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S", nullptr, false)) {
        }
        ImGui::Separator();

        if (ImGui::MenuItem("Quit", "Alt + F4")) {
            quit();
        }
        ImGui::EndMenu();
    }

    //
    // Edit menu
    //
    if (ImGui::BeginMenu("Edit", true /*enabled*/)) {
        if (ImGui::MenuItem("Undo", "Ctrl+Z", nullptr, false)) {
        }
        if (ImGui::MenuItem("Redo", "Ctrl+Y", nullptr, false)) {
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Clear Selection", nullptr, nullptr, false)) {
        }
        ImGui::EndMenu();
    }

    //
    // Windows Menu
    //
    if (ImGui::BeginMenu("Windows")) {
        ImGui::EndMenu();
    }

    //
    // Tools menu
    //
    if (ImGui::BeginMenu("Tools")) {
        ImGui::MenuItem("Show ImGui Demo", nullptr, &showDemoWindow);
        ImGui::MenuItem("Show ImGui Metric", nullptr, &showMetricsWindow);
        ImGui::MenuItem("Show ImGui Debug Log", nullptr, &showDebugLogWindow);
        ImGui::MenuItem("Show ImGui stack editor", nullptr, &showIDStackToolWindow);
        ImGui::EndMenu();
    }

    if (ImGui::MenuItem("About")) {
    }

    if (isMainMenuBarVisible) {
        ImGui::EndMainMenuBar();
    }
}

} // namespace fuse
