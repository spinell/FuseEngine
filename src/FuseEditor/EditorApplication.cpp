#include "EditorApplication.h"

#include "FuseCore/scene/Components.h"
#include "FuseCore/scene/Scene.h"
#include "panel/InspectorPanel.h"
#include "panel/LogPanel.h"
#include "panel/SceneHierachyPanel.h"
#include "panel/ScenePanel.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace {
bool showDemoWindow        = false;
bool showMetricsWindow     = false;
bool showDebugLogWindow    = false;
bool showIDStackToolWindow = false;

bool hierarchyOpen = true;
bool inspectorOpen = true;
bool consoleOpen   = true;
bool viewportOpen  = true;
} // namespace

namespace fuse {

EditorApplication::EditorApplication() = default;

EditorApplication::~EditorApplication() = default;

void EditorApplication::onUpdate(float /*deltaTime*/) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClearColor(1.0f, .0f, 1.f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EditorApplication::onEvent(const Event& /*event*/) {}

void EditorApplication::onImGui() {
    const bool isDockingEnable = (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) ==
                                 ImGuiConfigFlags_DockingEnable;
    if (isDockingEnable) {
        const ImGuiID dockspaceId = ImGui::GetID("DockSpace");
        if (ImGui::DockBuilderGetNode(dockspaceId) == nullptr) {
            ImGui::DockBuilderRemoveNode(dockspaceId); // Clear out existing layout
            ImGui::DockBuilderAddNode(
              dockspaceId,
              ImGuiDockNodeFlags_DockSpace /*| ImGuiDockNodeFlags_NoCloseButton*/); // Add empty nod
            ImGui::DockBuilderSetNodeSize(dockspaceId, ImGui::GetMainViewport()->Size);

            ImGuiID       dockMainId = dockspaceId;
            const ImGuiID dockIdLeft =
              ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Left, 0.2f, nullptr, &dockMainId);
            const ImGuiID dockIdRight =
              ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Right, 0.2f, nullptr, &dockMainId);
            const ImGuiID dockIdBottom =
              ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Down, 0.20f, nullptr, &dockMainId);

            ImGui::DockBuilderDockWindow("###Hierarchy", dockIdLeft);
            ImGui::DockBuilderDockWindow("###Inspector", dockIdRight);
            ImGui::DockBuilderDockWindow("###Console", dockIdBottom);
            ImGui::DockBuilderDockWindow("###Viewport", dockMainId);
            //ImGui::DockBuilderGetNode(dock_main_id)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
            //ImGui::DockBuilderGetNode(dock_main_id)->LocalFlags |= ImGuiDockNodeFlags_NoWindowMenuButton;
            ImGui::DockBuilderFinish(dockspaceId);
        }

        // DockSpaceOverViewport
        // This will create a window + call ImGui::DockSpace()
        ImGuiDockNodeFlags dockNodeFlags = ImGuiDockNodeFlags_None;
        //dockNodeFlags |= ImGuiDockNodeFlags_KeepAliveOnly;
        //dockNodeFlags |= ImGuiDockNodeFlags_NoDockingOverCentralNode;
        dockNodeFlags |= ImGuiDockNodeFlags_PassthruCentralNode;
        //dockNodeFlags |= ImGuiDockNodeFlags_NoDockingSplit;
        //dockNodeFlags |= ImGuiDockNodeFlags_NoResize;
        //dockNodeFlags |= ImGuiDockNodeFlags_AutoHideTabBar;
        //dockNodeFlags |= ImGuiDockNodeFlags_NoUndocking;
        //dockNodeFlags |= ImGuiDockNodeFlags_NoTabBar; // internal
        //dockNodeFlags |= ImGuiDockNodeFlags_HiddenTabBar; // internal
        //dockNodeFlags |= ImGuiDockNodeFlags_NoWindowMenuButton; // internal
        //dockNodeFlags |= ImGuiDockNodeFlags_NoCloseButton; // internal
        ImGui::DockSpaceOverViewport(dockspaceId,
                                     ImGui::GetMainViewport(),
                                     dockNodeFlags,
                                     nullptr /*windowClass*/);
    }

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

    mSceneHierarchyPanel->onImGui(hierarchyOpen);
    mInspectorPanel->onImGui(inspectorOpen);
    mLogPanel->onImGui(consoleOpen);
    mScenePanel->onImGui(viewportOpen);
}

bool EditorApplication::onInit() {
    mScene               = std::make_unique<Scene>();
    mSceneHierarchyPanel = std::make_unique<SceneHierarchyPanel>();
    mInspectorPanel      = std::make_unique<InspectorPanel>();
    mLogPanel            = std::make_unique<LogPanel>();
    mScenePanel          = std::make_unique<ScenePanel>();

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

    mScenePanel->setScene(mScene.get());
    mSceneHierarchyPanel->setScene(mScene.get());
    mSceneHierarchyPanel->setSelectionCallback(
      [&](Entity entity) { mInspectorPanel->setEntity(entity); });

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
        ImGui::MenuItem("Hierarchy", nullptr, &hierarchyOpen);
        ImGui::MenuItem("Console", nullptr, &consoleOpen);
        ImGui::MenuItem("Inspector", nullptr, &inspectorOpen);
        ImGui::MenuItem("Viewport", nullptr, &viewportOpen);
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

        auto& io = ImGui::GetIO();
        bool  dockingEnable =
          (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) == ImGuiConfigFlags_DockingEnable;
        if (ImGui::MenuItem("Enable Docking", nullptr, &dockingEnable)) {
            io.ConfigFlags ^= ImGuiConfigFlags_DockingEnable;
        }
        bool viewportEnable =
          (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) == ImGuiConfigFlags_ViewportsEnable;
        if (ImGui::MenuItem("Enable Viewport", nullptr, &viewportEnable)) {
            io.ConfigFlags ^= ImGuiConfigFlags_ViewportsEnable;
        }
        ImGui::EndMenu();
    }

    if (ImGui::MenuItem("About")) {
    }

    if (isMainMenuBarVisible) {
        ImGui::EndMainMenuBar();
    }
}

} // namespace fuse
