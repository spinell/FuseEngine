#include "Application.h"

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

    out vec4 FragColor;
    void main()
    {
        //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        FragColor = outColor;
    }
)";

} // namespace

Application::Application() = default;

Application::~Application() = default;

bool Application::onInit() {
    mVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertexShader, 1, &kVertexShaderSource, nullptr);
    glCompileShader(mVertexShader);
    int  success{};
    char infoLog[512];
    glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(mVertexShader, 512, nullptr, infoLog);
        spdlog::error("SHADER::VERTEX::COMPILATION_FAILED\n {}", infoLog);
    }


    mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragmentShader, 1, &kFragmentShaderSource, nullptr);
    glCompileShader(mFragmentShader);
    glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(mFragmentShader, 512, nullptr, infoLog);
        spdlog::error("SHADER::PIXEL::COMPILATION_FAILED\n {}", infoLog);
    }


    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragmentShader);
    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
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

void Application::onUpdate(float /*deltaTime*/) {
    glClearColor(.2f, .2f, .2f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const fuse::Mat4 translation = fuse::Mat4::CreateTranslation({0, 0, -11});
    const fuse::Mat4 scale       = fuse::Mat4::CreateScaling({1, 1, 1});
    const fuse::Mat4 rotation =
      fuse::Mat4::CreateRotation(fuse::degrees(10.0f) * mTimer.totalTime(), fuse::Vec3(1, 1, 0));
    fuse::Mat4  transform    = translation * rotation * scale;
    const GLint transformLoc = glGetUniformLocation(mShaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE /*transpose*/, transform.ptr());

    //
    // update camera
    //
    fuse::Mat4  proj    = mCamera.getProjMatrix();
    fuse::Mat4  view    = mCamera.getViewMatrix();
    const GLint viewLoc = glGetUniformLocation(mShaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE /*transpose*/, view.ptr());

    const GLint projLoc = glGetUniformLocation(mShaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_TRUE /*transpose*/, proj.ptr());

    glUseProgram(mShaderProgram);
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
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
    }
}

void Application::onImGui() { ImGui::ShowDemoWindow(); }
