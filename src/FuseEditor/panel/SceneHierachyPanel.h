#pragma once
#include <FuseCore/scene/Entity.h>
#include <entt/entity/entity.hpp>

#include <string>

namespace fuse {
class Scene;

/// @brief ImGui panel to display entity inthe a scene.
class SceneHierachyPanel {
public:
    SceneHierachyPanel();
    ~SceneHierachyPanel();

    SceneHierachyPanel(const SceneHierachyPanel&)            = delete;
    SceneHierachyPanel(SceneHierachyPanel&&)                 = delete;
    SceneHierachyPanel& operator=(const SceneHierachyPanel&) = delete;
    SceneHierachyPanel& operator=(SceneHierachyPanel&&)      = delete;

    /// @brief Set the scene used by the panel to display entity.
    /// @param scene The scene to used.
    void setScene(Scene* scene);

    void onImGui();

private:
    void drawEntityNode(Entity entity, const std::string& name);
    void drawMenuEntity3d();

private:
    Scene* mScene{};
    bool   mIsVisible{true};
    Entity mSelectedEntity;
};

} // namespace fuse
