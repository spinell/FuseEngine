#include "Scene.h"

#include <algorithm>
#include <print>

namespace fuse {

Scene::Scene() { mRegistry.ctx().emplace<Scene&>(*this); }

Scene& Scene::getRegistryAsScene(const entt::registry& registry) {
    const auto* scene = registry.ctx().find<Scene>();
    assert(scene && "scene is not in context.");
    return const_cast<Scene&>(*scene);
}

[[nodiscard]] Entity Scene::createEntity(std::string name) {
    entt::handle handle = {mRegistry, mRegistry.create()};

    if (name.empty()) {
        name = std::format("Entity ({})", getEntityCount());
    }

    handle.emplace<NameComponent>(std::move(name));
    handle.emplace<IDComponent>();

    return handle;
}

void Scene::destroyEntity(Entity& entity) noexcept {
    mRegistry.destroy(entity.mEntity);
    entity = {};
}

bool Scene::isEmpty() const noexcept { return mRegistry.storage<entt::entity>()->free_list() == 0; }

std::size_t Scene::getEntityCount() const noexcept {
    return mRegistry.storage<entt::entity>()->free_list();
}

void Scene::clear() noexcept { mRegistry.clear(); }

std::size_t Scene::getEntityComponentCount(const Entity& entity) const noexcept {
    std::size_t nbComponent = 0;
    for (const auto& [id, storage] : mRegistry.storage()) {
        if (storage.contains(entity.mEntity)) {
            nbComponent++;
        }
    }
    return nbComponent;
}

bool Scene::hasSameComponentType(const Entity& entity1, const Entity& entity2) const noexcept {
    return std::ranges::all_of(mRegistry.storage(), [&entity1, &entity2](const auto& it) {
        return it.second.contains(entity1.mEntity) == it.second.contains(entity2.mEntity);
    });
}

Entity Scene::duplicateEntity(const Entity& entity) {
    assert(entity && "Source entity is invalid.");
    if (!entity) {
        return {};
    }

    entt::handle newEntity = {mRegistry, mRegistry.create()};

    for (const auto& [id, storage] : mRegistry.storage()) {
        std::println("storageId={} name={} hash={} index={}",
                     id,
                     storage.type().name(),
                     storage.type().hash(),
                     storage.type().index());
        // only copy component if the source entity containts this component.
        if (storage.contains(entity.mEntity)) {
            // Calling storage.push() with data will call the copy contructor.
            // Without data, it will call the default constructor.
            // For the IDComponent, we don't want to copy the ID and end up with 2 entity withthe same id.
            if (id == entt::type_hash<IDComponent>()) {
                [[maybe_unused]] const auto it = storage.push(newEntity);
                assert(it != storage.end());
            } else {
                // this will call copy constructor if available,
                const void*                 componentData = storage.value(entity.mEntity);
                [[maybe_unused]] const auto it            = storage.push(newEntity, componentData);
                assert(it != storage.end());
            }
        }
    }

    return newEntity;
}

} // namespace fuse
