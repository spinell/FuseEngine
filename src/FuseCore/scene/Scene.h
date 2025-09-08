#pragma once
#include "Entity.h"

#include <entt/entity/handle.hpp>
#include <entt/entity/registry.hpp>

#include <string>

namespace fuse {

struct NameComponent {
    std::string name;

    auto operator<=>(const NameComponent&) const = default;
};

struct IDComponent {
    IDComponent() {
        static unsigned id = 0;
        mId                = id++;
    }

    auto operator<=>(const IDComponent&) const = default;

    unsigned mId;
};

class Scene {
public:
    /// @brief Default constructor. Create a empty scene.
    Scene();

    ~Scene() = default;

    /// @brief Copy constructor delete on purpose.
    Scene(const Scene&) = delete;

    /// @brief Move construcotr.
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
    [[nodiscard]] Entity createEntity(std::string name = {});

    /// @brief Delete a entity and it component from the scene.
    /// @param entity The entity to delete.
    void destroyEntity(Entity& entity) noexcept;

    /// @brief Dupicate (clone) a entity with it's compoenent.
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

    /// @brief Retrive the Entt registry.
    /// @param self
    /// @return The Entt entity.
    [[nodiscard]] auto& getRegistry(this auto&& self) noexcept { return self.mRegistry; }

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
    std::string    mName = "Untitle"; ///< The name ofthe scene.
    entt::registry mRegistry;
};

} // namespace fuse
