#pragma once
#include <FuseCore/math/Mat4.h>
#include <FuseCore/scene/Scene.h>

#include <glad/glad.h>

namespace fuse {

class SceneRenderer {
public:
    SceneRenderer();
    ~SceneRenderer();

    SceneRenderer(const SceneRenderer&) = delete;
    SceneRenderer(SceneRenderer&&)      = delete;

    SceneRenderer& operator=(const SceneRenderer&) = delete;
    SceneRenderer& operator=(SceneRenderer&&)      = delete;

    void renderScene(const Scene& scene, const fuse::Mat4& proj, const fuse::Mat4& view) const;

private:
    unsigned int mVertexShader   = 0;
    unsigned int mFragmentShader = 0;
    unsigned int mShaderProgram  = 0;
    unsigned int mVao            = 0;
    unsigned int mVbo            = 0;
};

} // namespace fuse
