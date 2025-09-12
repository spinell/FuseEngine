#include "EditorApplication.h"

#include "FuseCore/scene/Scene.h"
#include "panel/SceneHierachyPanel.h"

#include <imgui.h>

namespace {
bool showDemoWindow        = false;
bool showMetricsWindow     = false;
bool showDebugLogWindow    = false;
bool showIDStackToolWindow = false;
} // namespace

namespace fuse {

EditorApplication::EditorApplication()
    : fuse::Application() {
    mScene              = new Scene();
    mSceneHierachyPanel = new SceneHierachyPanel();
}

EditorApplication::~EditorApplication() {
    delete mScene;
    delete mSceneHierachyPanel;
}

void EditorApplication::onUpdate(float /*deltaTime*/) {
    // TODO: clear should go in base class
    glClearColor(1.0f, .2f, .2f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EditorApplication::onEvent(const Event& /*event*/) {}

void EditorApplication::onImGui() {
    //imguiDrawMainMenuBar();

    if (true /*showDemoWindow*/) {
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
}

bool EditorApplication::onInit() {
    mSceneHierachyPanel->setScene(mScene);
    return true;
}

void EditorApplication::onShutdown() {}

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
