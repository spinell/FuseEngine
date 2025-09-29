#pragma once
#include <FuseCore/math/Mat4.h>
#include <FuseCore/scene/Scene.h>

namespace fuse {

class TransformerSystem {
public:
    TransformerSystem()  = default;
    ~TransformerSystem() = default;

    TransformerSystem(const TransformerSystem&) = delete;
    TransformerSystem(TransformerSystem&&)      = delete;

    TransformerSystem& operator=(const TransformerSystem&) = delete;
    TransformerSystem& operator=(TransformerSystem&&)      = delete;

    void update(Scene& scene, float deltaTime);
};

} // namespace fuse
