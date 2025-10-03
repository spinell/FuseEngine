#include "NativeScriptSystem.h"

#include "components/CNativeScript.h"

namespace fuse {

void NativeScriptSystem::update(float deltaTime, entt::registry& registry, Scene* scene) noexcept {

    // First pass: onCreate
    registry.view<CNativeScript>().each(
      [deltaTime, &registry, scene](auto entity, CNativeScript& comp) {
        assert(comp.instance && "CNativeScript::instance is null");
        if (comp.instance->mEntity == entt::null) {
            comp.instance->mEntity   = entity;
            comp.instance->mScene    = scene;
            comp.instance->mRegistry = &registry;
            comp.instance->onCreate();
        }
          comp.instance->onUpdate(deltaTime);
      });

    // Second pass: onLastUpdate
    registry.view<CNativeScript>().each(
      [deltaTime](auto entity, CNativeScript& nsc) { nsc.instance->onLastUpdate(deltaTime); });
}


} // namespace fuse
