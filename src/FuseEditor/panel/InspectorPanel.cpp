#include "InspectorPanel.h"

#include <FuseApp/ImGui/Widget.h>
#include <FuseCore/math/Vec3.h>
#include <FuseCore/scene/components/Components.h>
#include <FuseEditor/embed/fonts/IconsMaterialDesignIcons.h>

#include <imgui.h>

namespace {
const char* panelName = ICON_MDI_INFORMATION " Inspector###Inspector";

/// @brief Draw an entity component
/// @tparam Component The type of component to render.
/// @tparam Callback
/// @param label
/// @param entity
/// @param callback
template <class Component, class Callback>
void drawComponent(const char* label, fuse::Entity entity, Callback callback) {
    ImGui::PushID(label);

    if (entity.hasComponents<Component>()) {
        const auto& contentRegionAvail = ImGui::GetContentRegionAvail();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4.F, 4.F});

        ImGuiTreeNodeFlags collapsingHeaderFlags = 0;
        collapsingHeaderFlags |= ImGuiTreeNodeFlags_DefaultOpen;
        collapsingHeaderFlags |= ImGuiTreeNodeFlags_AllowItemOverlap;
        const bool isOpen = ImGui::CollapsingHeader(label, collapsingHeaderFlags);

        const float lineHeight = ImGui::GetFontSize() + (ImGui::GetStyle().FramePadding.y * 2.0F);
        ImGui::SameLine(contentRegionAvail.x - (lineHeight * 0.5F));

        if (ImGui::Button("+", ImVec2{lineHeight, lineHeight})) {
            ImGui::OpenPopup("ComponentSettings");
        }
        ImGui::PopStyleVar();

        if (isOpen) {
            callback();
        }

        if (ImGui::BeginPopup("ComponentSettings")) {
            if (ImGui::MenuItem("Remove")) {
                entity.removeComponents<Component>();
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
    ImGui::PopID();
}

bool drawInputText(const std::string& label, std::string& text) {
    // TODO: FIXME
    char buffer[256]{};
    assert(text.size() < 256);
#ifdef _WIN32
    strncpy_s(buffer, sizeof(buffer), text.c_str(), text.size());
#else
    strncpy(buffer, text.c_str(), std::min(text.size(), sizeof(buffer)));
#endif
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);

    // draw the labal on the first column
    ImGui::SetColumnWidth(0, 100);
    ImGui::TextUnformatted(label.c_str());

    ImGui::NextColumn();
    const bool hasChanged = ImGui::InputText("##inputText", buffer, sizeof(buffer));
    text                  = buffer;

    ImGui::Columns(1);

    ImGui::PopID();

    return hasChanged;
}

/// @brief
/// @param label
/// @param angle
bool dragFloat(const std::string& label, float& value) {
    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100);
    ImGui::TextUnformatted(label.c_str());
    ImGui::NextColumn();
    const bool hasChanged = ImGui::DragFloat("##drag", &value);
    ImGui::Columns(1);
    ImGui::PopID();
    return hasChanged;
}

/// @brief
/// @param label
/// @param angle
void dragAngle(const std::string& label, fuse::Angle& angle) {
    auto degree = angle.asDegrees();
    if (dragFloat(label, degree)) {
        angle = fuse::degrees(degree);
    }
}

/// @brief Draw a 3d vector drag slider widget with button to reset the value.
/// @param label      The label to display.
/// @param values     The 3d vector to display/edit.
/// @param resetValue The value to use to reset the vector component.
/// @param columnWidth
void dragVec3(const std::string& label,
              fuse::Vec3&        values,
              float              resetValue  = 0.0F,
              float              columnWidth = 100.0F) {
    const ImGuiIO& io         = ImGui::GetIO();
    auto*          boldFont   = io.Fonts->Fonts[0];
    const float    lineHeight = ImGui::GetFontSize() + (ImGui::GetStyle().FramePadding.y * 2.0F);
    const ImVec2   buttonSize = {lineHeight + 3.0F, lineHeight};

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);

    // draw the labal on the first column
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::TextUnformatted(label.c_str());

    // draw each component vector on the next column.
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

    //
    // X component
    //
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8F, 0.1F, 0.15F, 1.0F});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9F, 0.2F, 0.2F, 1.0F});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8F, 0.1F, 0.15F, 1.0F});
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize)) {
        values.x = resetValue;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1F, 0.0F, 0.0F, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    //
    // Y component
    //
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2F, 0.7F, 0.2F, 1.0F});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3F, 0.8F, 0.3F, 1.0F});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2F, 0.7F, 0.2F, 1.0F});
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize)) {
        values.y = resetValue;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1F, 0.0F, 0.0F, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    //
    // Z component
    //
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1F, 0.25F, 0.8F, 1.0F});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2F, 0.35F, 0.9F, 1.0F});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1F, 0.25F, 0.8F, 1.0F});
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize)) {
        values.z = resetValue;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1F, 0.0F, 0.0F, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
}


} // namespace

namespace fuse {


InspectorPanel::InspectorPanel() = default;

void InspectorPanel::setEntity(Entity entity) { mEntity = entity; }

void InspectorPanel::onImGui(bool& isOpen) {
    if (!isOpen) {
        return;
    }

    const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
    mIsVisible                         = ImGui::Begin(panelName, &isOpen, windowFlags);
    if (mIsVisible && mEntity.isValid()) {
        if (mEntity.hasComponents<NameComponent>()) {
            auto name = mEntity.getComponent<NameComponent>().name;
            if (drawInputText("Name", name)) {
                mEntity.getComponent<NameComponent>().name = name;
            }
        }

        //ImGuiTextFmt("Name         {}", mEntity.getComponent<NameComponent>().name);
        ImGuiTextFmt("UID          {}", mEntity.getComponent<IDComponent>().id);
        ImGuiTextFmt("Entt         {}", entt::to_integral(mEntity.getId()));
        ImGuiTextFmt("Entt ID      {}", entt::to_entity(mEntity.getId()));
        ImGuiTextFmt("Entt Version {}", entt::to_version(mEntity.getId()));

        drawComponent<CTransform>(ICON_MDI_VECTOR_LINE " Transform", mEntity, [this]() {
            CTransform& cTransform = mEntity.getComponent<CTransform>();
            dragVec3("Translation", cTransform.translation);
            dragVec3("Roatation", cTransform.rotation);
            dragVec3("Scaling", cTransform.scale, 1.0f);
        });
        drawComponent<CMesh>("Mesh", mEntity, [this]() {
            CMesh& cMesh = mEntity.getComponent<CMesh>();
            ImGui::ColorEdit4("Color", &cMesh.color.x);
        });

        drawComponent<CRotator>("Rotator", mEntity, [this]() {
            CRotator& cRotator = mEntity.getComponent<CRotator>();
            dragAngle("Angle", cRotator.angle);
            dragVec3("Axis", cRotator.axis);
        });

        drawComponent<CTranslator>("Translator", mEntity, [this]() {
            CTranslator& cTranslator = mEntity.getComponent<CTranslator>();
            dragVec3("Direction", cTranslator.direction);
            dragFloat("Seconds", cTranslator.duration);
        });
    }

    ImGui::End();
}

} // namespace fuse
