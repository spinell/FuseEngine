#pragma once
#include "Entity.h"

#include <entt/entity/handle.hpp>
#include <entt/entity/registry.hpp>

#include <string>

namespace fuse {

class Scene {
public:
    /// @brief Default constructor. Create a empty scene.
    Scene();

    ~Scene() = default;

    /// @brief Copy constructor delete on purpose.
    Scene(const Scene&) = delete;

    /// @brief Move constructor.
    /// @param other The other scene to move on.
    Scene(Scene&& other) = default;

    /// @brief Move assignment deleted on purpose.
    Scene& operator=(const Scene&) = delete;

    /// @brief Move assignment.
    /// @param other The other scene to move on.
    Scene& operator=(Scene&&) = default;

    /// @brief Create a new entity.
    /// @param name The name of the entity.
    /// @return The new created entity.
    Entity createEntity(std::string name = {});

    /// @brief Delete a entity and it component from the scene.
    /// @param entity The entity to delete.
    void destroyEntity(Entity& entity) noexcept;

    /// @brief Duplicate (clone) a entity with it's comopenent.
    /// @param entity The entity to clone.
    /// @return The new entity.
    Entity duplicateEntity(const Entity& entity);

    /// @brief Query if the scene if empty or not.
    /// @return true if the scene is empty, false otherwise.
    [[nodiscard]] bool isEmpty() const noexcept;

    /// @brief Get the number of entity in the scene.
    /// @return The number of entity in the scene.
    [[nodiscard]] std::size_t getEntityCount() const noexcept;

    /// @brief Remove all entity and there component from the scene.
    void clear() noexcept;

#ifdef __cpp_explicit_this_parameter
    /// @brief Retrieve the Entt registry.
    /// @param self
    /// @return The Entt entity.
    [[nodiscard]] auto& getRegistry(this auto&& self) noexcept { return self.mRegistry; }
#else
    [[nodiscard]] entt::registry& getRegistry() noexcept { return mRegistry; }

    [[nodiscard]] const entt::registry& getRegistry() const noexcept { return mRegistry; }
#endif

    /// @brief Get the number of component for an entity.
    /// @param The entity to query the number of component for an entity.
    /// @return The number of component for an entity.
    [[nodiscard]] std::size_t getEntityComponentCount(const Entity& entity) const noexcept;

    /// @brief Check if all components of two entity are exactly the same type.
    /// @param entity1 The first entity.
    /// @param entity2 The second entity.
    /// @return true if all components of two entity are exactly the same type, false otherwise.
    [[nodiscard]] bool hasSameComponentType(const Entity& entity1,
                                            const Entity& entity2) const noexcept;


    [[nodiscard]] static Scene& getRegistryAsScene(const entt::registry& registry);

private:
    std::string    mName = "Untitle"; ///< The name of the scene.
    entt::registry mRegistry;
};

} // namespace fuse
