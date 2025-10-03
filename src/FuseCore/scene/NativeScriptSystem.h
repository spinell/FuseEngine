#pragma once
#include <entt/entity/registry.hpp>

namespace fuse {
class Scene;

/// @brief
class NativeScriptSystem {
public:
    NativeScriptSystem()  = default;
    ~NativeScriptSystem() = default;

    NativeScriptSystem(const NativeScriptSystem&)            = delete;
    NativeScriptSystem(NativeScriptSystem&&)                 = delete;
    NativeScriptSystem& operator=(const NativeScriptSystem&) = delete;
    NativeScriptSystem& operator=(NativeScriptSystem&&)      = delete;

    void update(float deltaTime, entt::registry& registry, Scene* scene) noexcept;
};

} // namespace fuse
