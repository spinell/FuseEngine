#pragma once
#include <entt/entity/registry.hpp>

#include <functional>

namespace fuse {
class Scene;
class NativeScriptSystem;

/// @brief Base class for native script components implementation.
class NativeScript {
public:
    NativeScript()          = default;
    virtual ~NativeScript() = default;

    NativeScript(const NativeScript&)            = delete;
    NativeScript& operator=(const NativeScript&) = delete;
    NativeScript(NativeScript&&)                 = delete;
    NativeScript& operator=(NativeScript&&)      = delete;

    /// @brief
    virtual void onCreate() {}

    /// @brief
    /// @param elapsed
    virtual void onUpdate(float /*elapsed*/) {}

    /// @brief
    /// @param elapsed
    virtual void onLastUpdate(float /*elapsed*/) {}

    /// @brief
    virtual void onDestroy() {}

protected:
    friend NativeScriptSystem;
    Scene*          mScene{};             //< The scene this script is attached to.
    entt::registry* mRegistry{};          //< The registry this script is attached to.
    entt::entity    mEntity = entt::null; //< The entity this script is attached to.
};

/// @brief
struct CNativeScript {

    /// @brief
    /// @param instance
    CNativeScript(NativeScript* instance)
        : instance(instance) {}

    virtual ~CNativeScript() { delete instance, instance = nullptr; }

    NativeScript* instance{}; //<
};

} // namespace fuse
