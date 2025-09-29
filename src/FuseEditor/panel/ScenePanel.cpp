#include "ScenePanel.h"

#include "FuseApp/ImGui/Widget.h"

#include <FuseEditor/embed/fonts/IconsMaterialDesignIcons.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace fuse {

ScenePanel::ScenePanel() {
    mEditorCamera.setPosition({0, 0, 10});
    mSceneRenderer = std::make_unique<SceneRenderer>();
}

ScenePanel::~ScenePanel() { mSceneRenderer.reset(); }

void ScenePanel::onImGui(bool& isOpen) {
    if (!isOpen) {
        return;
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1));
    if (ImGui::Begin(ICON_MDI_GAMEPAD_VARIANT " Viewport###Viewport", &isOpen)) {
        createOrResizeFBO(static_cast<int>(ImGui::GetContentRegionAvail().x),
                          static_cast<int>(ImGui::GetContentRegionAvail().y));

        mEditorCamera.update(ImGui::GetIO().DeltaTime);

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFbo);
        glClearColor(1.0f, .0f, .0f, 1.f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mEditorCamera.setAspectRatio(static_cast<float>(mWidth) / static_cast<float>(mHeight));
        const auto proj = mEditorCamera.getProjMatrix();
        const auto view = mEditorCamera.getViewMatrix();
        glViewport(0, 0, mWidth, mHeight);
        mSceneRenderer->renderScene(*mScene, proj, view);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        ImGui::GetWindowDrawList()->AddImage(mTexColorBuffer,
                                             ImGui::GetWindowPos(),
                                             ImGui::GetWindowPos() + ImGui::GetWindowSize(),
                                             ImVec2(0, 1) /*upper-left*/,
                                             ImVec2(1, 0) /*bottom-right*/);
        ImGuiTextFmt("GetContentRegionAvail {}x{}",
                     ImGui::GetContentRegionAvail().x,
                     ImGui::GetContentRegionAvail().y);
        ImGuiTextFmt("GetCursorScreenPos    {}x{}",
                     ImGui::GetCursorScreenPos().x,
                     ImGui::GetCursorScreenPos().y);
        ImGuiTextFmt("Window Position       {}x{}",
                     ImGui::GetWindowPos().x,
                     ImGui::GetWindowPos().y);
        ImGuiTextFmt("Window Size           {}x{}",
                     ImGui::GetWindowSize().x,
                     ImGui::GetWindowSize().y);
        ImGuiTextFmt("IsWindowFocused       {}", ImGui::IsWindowFocused());
        ImGuiTextFmt("IsWindowHovered       {}", ImGui::IsWindowHovered());
        ImGuiTextFmt("IsWindowDocked  {}", ImGui::IsWindowDocked());
        if (ImGui::IsWindowDocked()) {
            ImGuiTextFmt("Node Pos  {}x{}",
                         ImGui::GetWindowDockNode()->Pos.x,
                         ImGui::GetWindowDockNode()->Pos.y);
            ImGuiTextFmt("Node size {}x{}",
                         ImGui::GetWindowDockNode()->Size.x,
                         ImGui::GetWindowDockNode()->Size.y);
        }
    }
    ImGui::PopStyleColor(1);
    ImGui::End();
}

void ScenePanel::createOrResizeFBO(int width, int height) {
    if (mWidth == width && mHeight == height) {
        return;
    }
    mWidth  = width;
    mHeight = height;


    if (mFbo == 0) {
        glCreateTextures(GL_TEXTURE_2D, 1, &mTexColorBuffer);
        glCreateRenderbuffers(1, &mTexDepthBuffer);
        glCreateFramebuffers(1, &mFbo);
    } else {
        glDeleteTextures(1, &mTexColorBuffer);
        glDeleteRenderbuffers(1, &mTexDepthBuffer);

        glCreateTextures(GL_TEXTURE_2D, 1, &mTexColorBuffer);
        glCreateRenderbuffers(1, &mTexDepthBuffer);
        glCreateFramebuffers(1, &mFbo);
    }

    glTextureStorage2D(mTexColorBuffer, 1, GL_RGBA8 /*internalformat*/, mWidth, mHeight);
    glTextureParameteri(mTexColorBuffer, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(mTexColorBuffer, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glNamedRenderbufferStorage(mTexDepthBuffer,
                               GL_DEPTH24_STENCIL8 /*internalformat*/,
                               mWidth,
                               mHeight);


    glNamedFramebufferTexture(mFbo, GL_COLOR_ATTACHMENT0, mTexColorBuffer, 0 /*level*/);
    glNamedFramebufferRenderbuffer(mFbo,
                                   GL_DEPTH_STENCIL_ATTACHMENT,
                                   GL_RENDERBUFFER,
                                   mTexDepthBuffer);
}

} // namespace fuse
