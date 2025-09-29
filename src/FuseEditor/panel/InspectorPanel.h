#pragma once
#include "EditorPanel.h"

#include <FuseCore/scene/Entity.h>

namespace fuse {

/// @brief ImGui panel to display entity properties.
class InspectorPanel : public EditorPanel {
public:
    InspectorPanel();
    ~InspectorPanel() override = default;

    InspectorPanel(const InspectorPanel&)            = delete;
    InspectorPanel(InspectorPanel&&)                 = delete;
    InspectorPanel& operator=(const InspectorPanel&) = delete;
    InspectorPanel& operator=(InspectorPanel&&)      = delete;

    /// @brief Set the entity to display properties.
    /// @param entity The entity to used.
    void setEntity(Entity entity);

    void onImGui(bool& isOpen) override;

private:
    bool   mIsVisible{true};
    Entity mEntity;
};

} // namespace fuse
