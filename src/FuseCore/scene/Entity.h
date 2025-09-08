#pragma once
#include <entt/entity/entity.hpp>
#include <entt/entity/handle.hpp>
#include <entt/entity/registry.hpp>

#include <cassert>

namespace fuse {

/// @brief Entity represente an object into a scene.
/// @todo implement erase_if
/// @todo insert in
/// @todo add component concept
class Entity final {
public:
    /// @brief Default contructor. Create a invalid entity.
    Entity() noexcept = default;

    ~Entity() noexcept                               = default;
    Entity(const Entity&) noexcept                   = default;
    Entity& operator=(const Entity&) noexcept        = default;
    Entity(Entity&&) noexcept                        = default;
    Entity& operator=(Entity&&) noexcept             = default;
    bool    operator==(const Entity&) const noexcept = default;

    /// @copydoc isValid
    [[nodiscard]] explicit operator bool() const noexcept { return isValid(); }

    /// @brief Checks if a entity refers to a valid entity or not.
    /// @return True if the entity refers to a valid entity, false otherwise.
    [[nodiscard]] bool isValid() const noexcept { return mEntity.valid(); }

    void destroy() {
        mEntity.destroy();
        mEntity = {};
    }

    /// @brief Add a new component to this entity.
    ///
    /// The component must have a proper constructor or be of aggregate type.
    /// The entity should not already have this type of component.
    ///
    /// @tparam Type Type of component to create
    /// @tparam Args Types of arguments to use to construct the component.
    /// @param  args Parameters to use to initialize the component.
    /// @return A reference to the newly created component or @b void for empty type.
    /// @warning Attempting to assign a component to an entity that already owns
    ///         it results in undefined behavior.
    template <class Type, class... Args>
    decltype(auto) addComponent(Args... args) {
        assert(!hasComponents<Type>());
        return mEntity.emplace<Type>(std::forward<Args>(args)...);
    }

    /// @brief Add or replaces the given component for this entity.
    ///
    /// The component must have a proper constructor or be of aggregate type.
    ///
    /// @tparam Type Type of component to assign or replace.
    /// @tparam Args Types of arguments to use to construct the component.
    /// @param  args Parameters to use to initialize the component.
    /// @return A reference to the newly created component or @b void for empty type.
    template <class Type, class... Args>
    decltype(auto) addOrReplaceComponent(Args... args) {
        return mEntity.emplace_or_replace<Type>(std::forward<Args>(args)...);
    }

    /// \brief Patches the given component for an entity.
    ///
    /// The signature of the function should be equivalent to the following:
    ///
    /// @code{.cpp}
    /// void(Type &); // for no empty type
    /// void();       // for empty type.
    /// @endcode
    ///
    /// @tparam Type Type of component to patch.
    /// @tparam Func Types of the function objects to invoke.
    /// @param func  Valid function objects.
    /// @return A reference to the patched component or void for empty type.
    /// @warning Attempting to patch a component of an entity that doesn't own it
    ///          results in undefined behavior.
    template <class Type, class... Func>
    // NOLINTNEXTLINE(modernize-use-nodiscard)
    decltype(auto) patchComponent(Func&&... func) const {
        assert(hasComponents<Type>());
        return mEntity.patch<Type>(std::forward<Func>(func)...);
    }

    /// @brief Replaces the given component for this entity.
    ///
    /// The component must have a proper constructor or be of aggregate type.
    ///
    /// @tparam Type Type of component to replace.
    /// @tparam Args Types of arguments to use to construct the component.
    /// @param args  Parameters to use to initialize the component.
    /// @return A reference to the component being replaced or void for empty type.
    ///	@warning Attempting to replace a component of an entity that doesn't own it
    ///		     results in undefined behavior.
    template <class Type, class... Args>
    // NOLINTNEXTLINE(modernize-use-nodiscard)
    decltype(auto) replaceComponent(Args&&... args) const {
        assert(hasComponents<Type>());
        return mEntity.replace<Type>(std::forward<Args>(args)...);
    }

    /// @brief Removes the given component from an entity.
    /// @tparam Type   Type of component to remove.
    /// @tparam Others Other types of components to remove.
    /// @return The number of components actually removed.
    template <class Type, class... Others>
    std::size_t removeComponents() noexcept {
        return (mEntity.remove<Type>() + ... + mEntity.remove<Others>());
    }

    /// @brief Erases the given components from this entity.
    ///
    /// The entity most contains each components to remove.
    ///
    /// @tparam Type   Types of component to erase.
    /// @tparam Others Other types of components to erase.
    /// @warning Attempting to erase a component from an entity that doesn't own it
    ///          results in undefined behavior.
    template <class Type, class... Others>
    void eraseComponents() noexcept {
        assert(hasComponents<Type>() && hasComponents<Others...>());
        (mEntity.erase<Type>(), (mEntity.erase<Others>(), ...));
    }

    /// @todo
    template <typename Func>
    void eraseComponentsIf(Func func);

    /// @todo multi component
    /// @brief Return a reference to a component of this entity.
    /// @tparam Type Types of components to get.
    /// @return References to the components owned by this entity.
    /// @warning Attempting to assign a component to an entity that already owns it
    ///          results in undefined behavior.
    template <typename... Type>
    [[nodiscard]] decltype(auto) getComponent() const noexcept {
        static_assert(((!std::is_empty_v<Type>) && ...), "Can't get a pointer to a empty type.");
        assert(hasComponents<Type...>());
        return mEntity.get<Type...>();
    }

    /// \brief Return a reference to a component of this entity.
    ///
    ///	In case the entity doesn't own the component, the parameters provided are
    /// used to construct it.
    ///
    /// \tparam Type Types of components to get.
    /// \tparam Args Types of arguments to use to construct the component.
    /// \param  args Parameters to use to initialize the component.
    /// \return References to the components owned by this entity.
    template <class Type, class... Args>
    decltype(auto) getOrAddComponent(Args... args) {
        return mEntity.get_or_emplace<Type>(std::forward<Args>(args)...);
    }

    /// @brief Returns pointers to the given components for a handle.
    /// @tparam Type Types of components to get.
    /// @return Pointers to the components owned by the handle.
    /// @note The registry retains ownership of the pointed - to components.
    template <class... Type>
    [[nodiscard]] auto tryGetComponent() const noexcept {
        static_assert(((!std::is_empty_v<Type>) && ...), "Can't get a pointer to a empty type.");
        return mEntity.try_get<Type...>();
    }

    /// \brief Check if the entity have the given components.
    /// \tparam T Components for which to perform the check.
    /// \return Return true if the entity have all the given component, otherwise false.
    template <class... T>
    [[nodiscard]] bool hasComponents() const noexcept {
        return isValid() && mEntity.all_of<T...>();
    }

    /// \brief Checks if a entity has at least one of the given components.
    /// \tparam T Components for which to perform the check.
    /// \return True if the entity has at least one of the given components, false otherwise.
    template <typename... T>
    [[nodiscard]] bool hasAnyComponents() const noexcept {
        return isValid() && mEntity.any_of<T...>();
    }

private:
    friend class Scene;

    /// @brief Create a entity from a entt entity and the registry
    /// @param entity   The entt entity.
    /// @param registry The entt registry.
    Entity(entt::entity entity, entt::registry& registry) noexcept
        : mEntity(registry, entity) {}

    /// @brief Create a entity from a entt handle
    /// @param handle A valid entt::handle
    Entity(entt::handle handle) noexcept
        : mEntity(handle) {}

    entt::handle mEntity; ///< The Entt entity handle (pair of entt::entity + entt::registry).
};

} // namespace fuse
