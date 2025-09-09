#include "Application.h"

#include <FuseCore/scene/Components.h>

#include <imgui.h>
#include <spdlog/spdlog.h>

namespace {


// clang-format off
constexpr float kVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // back
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // front
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // left
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };


// clang-format on

constexpr const char* kVertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in  vec3 aPos;
    layout (location = 1) in  vec4 aColor;
    out vec4 outColor;

    uniform mat4 proj;
    uniform mat4 view;
    uniform mat4 transform;

    void main()
    {
        outColor = aColor;
        gl_Position = proj * view * transform * vec4(aPos, 1.0f);
    }
)";

constexpr const char* kFragmentShaderSource = R"(
    #version 330 core
    in  vec4 outColor;

    uniform vec4 color;

    out vec4 FragColor;
    void main()
    {
        //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        FragColor = color * outColor;
    }
)";

fuse::Entity entityToDestroy;


fuse::Entity createCube(fuse::Scene& scene, const fuse::Vec3& position,
                        const fuse::Vec4& color = fuse::Vec4{1.f, 1.f, 1.f, 1.f}) {
    fuse::Entity entity = scene.createEntity();

    auto& transform    = entity.addComponent<fuse::CTransform>();
    transform.position = position;

    auto& mesh = entity.addComponent<fuse::CMesh>();
    mesh.color = color;

    return entity;
}


} // namespace



Application::Application() = default;

Application::~Application() = default;

bool Application::onInit() {
    createCube(mScene, {0, 0, -11}).addComponent<fuse::CRotator>();
    createCube(mScene,{-11, 0, -11});

    mVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertexShader, 1, &kVertexShaderSource, nullptr);
    glCompileShader(mVertexShader);
    int  success{};
    char infoLog[512];
    glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(mVertexShader, 512, nullptr, infoLog);
        spdlog::error("SHADER::VERTEX::COMPILATION_FAILED\n {}", infoLog);
    }


    mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragmentShader, 1, &kFragmentShaderSource, nullptr);
    glCompileShader(mFragmentShader);
    glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(mFragmentShader, 512, nullptr, infoLog);
        spdlog::error("SHADER::PIXEL::COMPILATION_FAILED\n {}", infoLog);
    }


    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragmentShader);
    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (success  == GL_FALSE) {
        glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);
        spdlog::error("SHADER::PROGRAM::COMPILATION_FAILED\n {}", infoLog);
    }
    glUseProgram(mShaderProgram);


    glGenBuffers(1, &mVbo);


    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(20));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    return true;
}

void Application::onShutdown() {
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);
    glDeleteVertexArrays(1, &mVao);
    glDeleteBuffers(1, &mVbo);
}

void Application::onUpdate(float deltaTime) {
    glClearColor(.2f, .2f, .2f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //
    // update camera
    //
    fuse::Mat4  proj    = mCamera.getProjMatrix();
    fuse::Mat4  view    = mCamera.getViewMatrix();
    const GLint viewLoc = glGetUniformLocation(mShaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE /*transpose*/, view.ptr());

    const GLint projLoc = glGetUniformLocation(mShaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_TRUE /*transpose*/, proj.ptr());


    for (auto&& [entity, transform, mesh] :
         mScene.getRegistry().view<fuse::CTransform, fuse::CMesh>().each()) {

        const auto translationMat = fuse::Mat4::CreateTranslation(transform.position);
        const auto scaleMat       = fuse::Mat4::CreateScaling(transform.scale);
        auto       rotationMat    = fuse::Mat4::kIdentity;

        if (auto* translator = mScene.getRegistry().try_get<fuse::CTranslator>(entity)) {
            if (translator->duration > 0) {
                transform.position += translator->direction * deltaTime;
                translator->duration -= deltaTime;
            } else {
                mScene.getRegistry().remove<fuse::CTranslator>(entity);
            }
        }

        if (mScene.getRegistry().try_get<fuse::CRotator>(entity)) {
            rotationMat = fuse::Mat4::CreateRotation(fuse::degrees(10.0f) * getGameTimer().totalTime(),
                                                     fuse::Vec3(1, 1, 0));
        }


        const auto transformMat = translationMat * rotationMat * scaleMat;

        const GLint transformLoc = glGetUniformLocation(mShaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_TRUE /*transpose*/, transformMat.ptr());

        const GLint colorLoc = glGetUniformLocation(mShaderProgram, "color");
        glUniform4f(colorLoc, mesh.color.x, mesh.color.y, mesh.color.z, mesh.color.w);

        glUseProgram(mShaderProgram);
        glBindVertexArray(mVao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Application::onEvent(const fuse::Event& event) {
    fuse::Application::onEvent(event);

    if (const auto* resizedEvent = event.getIf<fuse::WindowResizedEvent>()) {
        glViewport(0, 0, resizedEvent->getWidth(), resizedEvent->getHeight());
        mCamera.setAspectRatio(static_cast<float>(resizedEvent->getWidth()) /
                               static_cast<float>(resizedEvent->getHeight()));
    } else if (const auto* moveEvent = event.getIf<fuse::MouseMovedEvent>()) {
        // Make each pixel correspond to a 1/8 of a degree.
        auto dx =
          fuse::degrees(0.125f) * moveEvent->getMouseDelta().first; // rotation around local Up
        auto dy =
          fuse::degrees(0.125f) * moveEvent->getMouseDelta().second; // rotation around local right
        mCamera.pitch(-dy);
        mCamera.yaw(-dx);
    } else if (const auto* keyEvent = event.getIf<fuse::KeyPressedEvent>()) {
        if (keyEvent->getScanCode() == fuse::ScanCode::A) {
            auto pos = mCamera.getPosition();
            pos -= mCamera.getRight() * 2;
            mCamera.setPosition(pos);
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::D) {
            auto pos = mCamera.getPosition();
            pos += mCamera.getRight() * 2;
            mCamera.setPosition(pos);
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::W) {
            auto pos = mCamera.getPosition();
            pos += mCamera.getDirection() * 2;
            mCamera.setPosition(pos);
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::S) {
            auto pos = mCamera.getPosition();
            pos -= mCamera.getDirection() * 2;
            mCamera.setPosition(pos);
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::Q) {
            auto pos = mCamera.getPosition();
            pos += fuse::Vec3::kAxisY;
            mCamera.setPosition(pos);
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::E) {
            auto pos = mCamera.getPosition();
            pos += fuse::Vec3::kAxisYNeg;
            mCamera.setPosition(pos);
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::Z) {
            entityToDestroy                                   = createCube(mScene, {0, 0, 0});
            entityToDestroy.getComponent<fuse::CMesh>().color = {0.5f, 0.5f, 0.5f, 1.0f};
            entityToDestroy.addComponent<fuse::CTranslator>(fuse::Vec3{1, 0, 0}, 2.0f);
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::X) {
            entityToDestroy.destroy();
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::C) {
            auto newEnt = mScene.duplicateEntity(entityToDestroy);
            newEnt.getOrAddComponent<fuse::CTranslator>(fuse::Vec3{0, 1, 0}, 2.0f);
        }
    }
}

void Application::onImGui() {
    ImGui::ShowDemoWindow();

    if (ImGui::Begin("Entities")) {
        for (auto entity : mScene.getRegistry().view<entt::entity>()) {
            ImGui::Text("%s id=%d",
                        mScene.getRegistry().get<fuse::NameComponent>(entity).name.c_str(),
                        mScene.getRegistry().get<fuse::IDComponent>(entity).mId);

            if (mScene.getRegistry().try_get<fuse::CTranslator>(entity)) {
                ImGui::Text("Translator");
            }
        }
    }
    ImGui::End();
}
