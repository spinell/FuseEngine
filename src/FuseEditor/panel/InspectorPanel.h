#pragma once
#include <FuseCore/scene/Entity.h>

namespace fuse {

/// @brief ImGui panel to display entity properties.
class InspectorPanel {
public:
    InspectorPanel();
    ~InspectorPanel() = default;

    InspectorPanel(const InspectorPanel&)            = delete;
    InspectorPanel(InspectorPanel&&)                 = delete;
    InspectorPanel& operator=(const InspectorPanel&) = delete;
    InspectorPanel& operator=(InspectorPanel&&)      = delete;

    /// @brief Set the entity to display properties.
    /// @param entity The entity to used.
    void setEntity(Entity entity);

    void onImGui();

private:
    bool   mIsVisible{true};
    Entity mEntity;
};

} // namespace fuse
