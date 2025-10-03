#include "TransformerSystem.h"

#include <FuseCore/scene/components/Components.h>

namespace fuse {

//NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void TransformerSystem::update(Scene& scene, float deltaTime) {
    auto& registry = scene.getRegistry();

    for (auto&& [entity, transform, rotator] : registry.view<CTransform, CRotator>().each()) {
        transform.rotation.y += (rotator.angle * deltaTime).asDegrees();
    }

    for (auto&& [entity, transform, translator] : registry.view<CTransform, CTranslator>().each()) {
        if (translator.duration > 0) {
            transform.translation += translator.direction * deltaTime;
            translator.duration -= deltaTime;
        } else {
            registry.remove<fuse::CTranslator>(entity);
        }
    }
}

} // namespace fuse
