#include "SceneHierachyPanel.h"

#include <FuseApp/ImGui/Widget.h>
#include <FuseCore/scene/components/Components.h>
#include <FuseCore/scene/Scene.h>
#include <FuseEditor/embed/fonts/IconsMaterialDesignIcons.h>

#include <imgui.h>
#include <spdlog/spdlog.h>

namespace {
const char* panelName = ICON_MDI_FILE_TREE " Hierarchy###Hierarchy";
}

namespace fuse {

SceneHierarchyPanel::SceneHierarchyPanel() = default;

SceneHierarchyPanel::~SceneHierarchyPanel() = default;

void SceneHierarchyPanel::setScene(Scene* scene) { mScene = scene; }

void SceneHierarchyPanel::onImGui(bool& isOpen) {
    if (!isOpen) {
        return;
    }

    if (!mScene) {
        return;
    }

    const ImGuiWindowFlags windowFlags = 0;
    mIsVisible                         = ImGui::Begin(panelName, &isOpen, windowFlags);
    if (mIsVisible) {
        auto& registry   = mScene->getRegistry();
        auto  entityView = registry.view<NameComponent>();
        for (auto e : entityView) {
            const Entity entity(e, registry);
            drawEntityNode(entity, entityView.get<NameComponent>(e).name);
        }
    }

    //
    // hierarchy panel Context menu
    //
    const ImGuiPopupFlags contextWindowFlags =
      ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_NoReopen;
    if (ImGui::BeginPopupContextWindow("ContextMenu", contextWindowFlags)) {
        if (ImGui::MenuItem("Create Empty Entity", nullptr, nullptr)) {
            Entity entity = mScene->createEntity("New Entity");
            entity.addComponent<CTransform>();
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
        if (mOnSelectionCallback) {
            mOnSelectionCallback({});
        }
    }

    ImGui::End();
}

void SceneHierarchyPanel::drawEntityNode(Entity entity, const std::string& name) {

    ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_None;
    nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow;
    nodeFlags |= ImGuiTreeNodeFlags_AllowOverlap;
    // nodeFlags |= ImGuiTreeNodeFlags_SpanFullWidth;
    nodeFlags |= ImGuiTreeNodeFlags_SpanAvailWidth;

    if (entity == mSelectedEntity) {
        nodeFlags |= ImGuiTreeNodeFlags_Selected;
    }

    ImGui::PushID(static_cast<int>(entity.getComponent<IDComponent>().id));
    const std::string nameWithIcon = ICON_MDI_CUBE_OUTLINE " " + name;
    if (ImGui::TreeNodeEx(nameWithIcon.c_str(), nodeFlags)) {
        //
        // Tree node is open.
        //
        ImGui::TreePop();
    }

    if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
        mSelectedEntity = entity;
        if (mOnSelectionCallback) {
            mOnSelectionCallback(entity);
        }
    }

    //
    // Entity context menu
    //
    const ImGuiPopupFlags entityContextWindowFlags =
      ImGuiPopupFlags_MouseButtonRight |
      ImGuiPopupFlags_NoReopen; // TODO: ImGuiPopupFlags_NoReopen does not seams to work
    if (ImGui::BeginPopupContextItem(nullptr, entityContextWindowFlags)) {

        if (ImGui::MenuItem("Delete Entity", nullptr, nullptr)) {
            entity.destroy();
        }
        if (ImGui::MenuItem("Duplicate Entity", nullptr, nullptr)) {
            mScene->duplicateEntity(entity);
        } else if (ImGui::MenuItem("Add Mesh", nullptr, nullptr)) {
            entity.addComponent<CMesh>();
        } else if (ImGui::MenuItem("Add rotator", nullptr, nullptr)) {
            entity.addComponent<CRotator>();
        } else if (ImGui::MenuItem("Add translator", nullptr, nullptr)) {
            entity.addComponent<CTranslator>();
        }

        ImGui::EndPopup();
    }

    ImGui::PopID();
}

void SceneHierarchyPanel::drawMenuEntity3d() {
    if (ImGui::BeginMenu("3D Object")) {
        if (ImGui::MenuItem("Cube")) {
            Entity entity = mScene->createEntity("Cube");
            entity.addComponent<CTransform>();
            entity.addComponent<CMesh>();
        } else if (ImGui::MenuItem("Sphere", nullptr, nullptr, false)) {
            mScene->createEntity("Sphere");
        } else if (ImGui::MenuItem("Plane", nullptr, nullptr, false)) {
            mScene->createEntity("Plane");
        } else if (ImGui::MenuItem("Cylinder", nullptr, nullptr, false)) {
            mScene->createEntity("Cylinder");
        }
        ImGui::EndMenu();
    }
}

} // namespace fuse
