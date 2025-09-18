#pragma once
#include "EditorPanel.h"

#include <FuseCore/scene/Entity.h>

#include <entt/entity/entity.hpp>

#include <functional>
#include <string>

namespace fuse {
class Scene;

/// @brief ImGui panel to display entity in the a scene.
class SceneHierarchyPanel : public EditorPanel {
public:
    SceneHierarchyPanel();
    ~SceneHierarchyPanel() override;

    SceneHierarchyPanel(const SceneHierarchyPanel&)            = delete;
    SceneHierarchyPanel(SceneHierarchyPanel&&)                 = delete;
    SceneHierarchyPanel& operator=(const SceneHierarchyPanel&) = delete;
    SceneHierarchyPanel& operator=(SceneHierarchyPanel&&)      = delete;

    /// @brief Set the scene used by the panel to display entity.
    /// @param scene The scene to used.
    void setScene(Scene* scene);

    void setSelectionCallback(std::function<void(Entity)> callback) {
        mOnSelectionCallback = std::move(callback);
    }

    void onImGui(bool& isOpen) override;

private:
    void drawEntityNode(Entity entity, const std::string& name);
    void drawMenuEntity3d();

    Scene*                      mScene{};
    bool                        mIsVisible{true};
    Entity                      mSelectedEntity;
    std::function<void(Entity)> mOnSelectionCallback;
};

} // namespace fuse
