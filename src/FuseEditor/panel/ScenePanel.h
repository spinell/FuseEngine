#pragma once
#include "../EditorCamera.h"
#include "EditorPanel.h"
#include "FuseApp/SceneRenderer.h"

#include <glad/glad.h>

namespace fuse {
class Scene;

class ScenePanel : public EditorPanel {
public:
    ScenePanel();
    ~ScenePanel() override;

    ScenePanel(const ScenePanel&)            = delete;
    ScenePanel(ScenePanel&&)                 = delete;
    ScenePanel& operator=(const ScenePanel&) = delete;
    ScenePanel& operator=(ScenePanel&&)      = delete;

    void onImGui(bool& isOpen) override;

    /// @brief Set the scene used by the panel to display entity.
    /// @param scene The scene to used.
    void setScene(Scene* scene) { mScene = scene; }

private:
    void                           createOrResizeFBO(int width, int height);
    Scene*                         mScene{};
    GLuint                         mFbo            = 0;
    GLuint                         mTexColorBuffer = 0;
    GLuint                         mTexDepthBuffer = 0;
    int                            mWidth          = 0;
    int                            mHeight         = 0;
    std::unique_ptr<SceneRenderer> mSceneRenderer;
    EditorCamera                   mEditorCamera;
};


} // namespace fuse
