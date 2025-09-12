#include "EditorApplication.h"

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
    mSceneHierachyPanel = std::make_unique<SceneHierachyPanel>();
    mInspectorPanel     = std::make_unique<InspectorPanel>();
}

EditorApplication::~EditorApplication() = default;

void EditorApplication::onUpdate(float /*deltaTime*/) {
    // TODO: clear should go in base class
    glClearColor(1.0f, .2f, .2f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const auto proj = Mat4::CreateProjectionPerspectiveFOVY(degrees(45), 4.f / 3.f, 0.1f, 1000.f);
    //const auto proj = Mat4::CreateProjectionOrthographicOffCenter(-20, 20, -20, 20, 0.1, 1000.f);
    const auto view = Mat4::CreateViewLookTo({0, 0, 10}, {0, 0, -10}, Vec3::kAxisY);
    //const auto view = Mat4::CreateViewLookAt({0, 0, 10}, {0, 0, 0}, Vec3::kAxisY);
    mSceneRenderer->renderScene(*mScene, proj, view);
}

void EditorApplication::onEvent(const Event& /*event*/) {}

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

    mSceneHierachyPanel->onImGui();
    mInspectorPanel->onImGui();
}

bool EditorApplication::onInit() {
    mSceneHierachyPanel->setScene(mScene.get());
    mSceneHierachyPanel->setSelectionCallback(
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
