#include "SceneHierachyPanel.h"

#include <FuseApp/ImGui/Widget.h>
#include <FuseCore/scene/Scene.h>

#include <imgui.h>
#include <spdlog/spdlog.h>

namespace fuse {

const char* panelName = "Hierachy";

SceneHierachyPanel::SceneHierachyPanel() {}

SceneHierachyPanel::~SceneHierachyPanel() {}

void SceneHierachyPanel::setScene(Scene* scene) { mScene = scene; }

void SceneHierachyPanel::onImGui() {
    if (!mScene) {
        return;
    }

    ImGuiWindowFlags windowFlags = 0;
    //windowFlags |= ImGuiWindowFlags_NoTitleBar;
    //windowFlags |= ImGuiWindowFlags_NoResize;
    //windowFlags |= ImGuiWindowFlags_NoMove;
    //windowFlags |= ImGuiWindowFlags_NoScrollbar;
    //windowFlags |= ImGuiWindowFlags_NoScrollWithMouse;
    //windowFlags |= ImGuiWindowFlags_NoCollapse;
    //windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
    //windowFlags |= ImGuiWindowFlags_NoBackground;
    //windowFlags |= ImGuiWindowFlags_NoSavedSettings;
    //windowFlags |= ImGuiWindowFlags_NoMouseInputs;
    //windowFlags |= ImGuiWindowFlags_MenuBar;
    //windowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
    //windowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
    //windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    //windowFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
    //windowFlags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
    //windowFlags |= ImGuiWindowFlags_NoNavInputs;
    //windowFlags |= ImGuiWindowFlags_NoNavFocus;
    //windowFlags |= ImGuiWindowFlags_UnsavedDocument;
    //windowFlags |= ImGuiWindowFlags_NoDocking;
    mIsVisible = ImGui::Begin("Hierachy", nullptr, windowFlags);
    if (mIsVisible) {
        auto& registry   = mScene->getRegistry();
        auto  entityView = registry.view<NameComponent>();
        for (auto e : entityView) {
            Entity entity(e, registry);
            drawEntityNode(entity, entityView.get<NameComponent>(e).name);
        }
    }

    //
    // hierachy panel Context menu
    //
    const ImGuiPopupFlags contextWindowFlags =
      ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_NoReopen;
    if (ImGui::BeginPopupContextWindow("ContextMenu", contextWindowFlags)) {
        if (ImGui::MenuItem("Create Empty Entity", nullptr, nullptr)) {
            mScene->createEntity("New Entity");
        }

        drawMenuEntity3d();

        ImGui::EndPopup();
    }

    //
    // Clear the selection when clicking into the hierachy panel
    //
    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_None) &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        mSelectedEntity = {};
    }

    ImGui::End();
}

void SceneHierachyPanel::drawEntityNode(Entity entity, const std::string& name) {

    ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_None;
    nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow;
    nodeFlags |= ImGuiTreeNodeFlags_AllowOverlap;
    // nodeFlags |= ImGuiTreeNodeFlags_SpanFullWidth;
    nodeFlags |= ImGuiTreeNodeFlags_SpanAvailWidth;

    if (entity == mSelectedEntity) {
        nodeFlags |= ImGuiTreeNodeFlags_Selected;
    }

    ImGui::PushID(static_cast<int>(entity.getComponent<IDComponent>().mId));
    if (ImGui::TreeNodeEx(name.c_str(), nodeFlags)) {
        //
        // Tree node is open.
        //
        ImGui::TreePop();
    }

    if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
        mSelectedEntity = entity;
    }

    //
    // Entity context menu
    //
    const ImGuiPopupFlags entityContextWindowFlags =
      ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoReopen; // TODO: ImGuiPopupFlags_NoReopen does not seams to work
    if (ImGui::BeginPopupContextItem(nullptr, entityContextWindowFlags)) {

        if (ImGui::MenuItem("Delete Entity", nullptr, nullptr)) {
            entity.destroy();
        }

        ImGui::EndPopup();
    }

    ImGui::PopID();
}

void SceneHierachyPanel::drawMenuEntity3d() {
    if (ImGui::BeginMenu("3D Object")) {
        if (ImGui::MenuItem("Cube")) {
            mScene->createEntity("Cube");
        } else if (ImGui::MenuItem("Sphere")) {
            mScene->createEntity("Sphere");
        } else if (ImGui::MenuItem("Plane")) {
            mScene->createEntity("Plane");
        } else if (ImGui::MenuItem("Cylinder")) {
            mScene->createEntity("Cylinder");
        }
        ImGui::EndMenu();
    }
}

} // namespace fuse
