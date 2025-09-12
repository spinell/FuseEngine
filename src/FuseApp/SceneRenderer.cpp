#include "SceneRenderer.h"

#include <FuseCore/scene/Components.h>

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


} // namespace

namespace fuse {

SceneRenderer::SceneRenderer() {
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
    if (success == GL_FALSE) {
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
}

SceneRenderer::~SceneRenderer() {
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);
    glDeleteVertexArrays(1, &mVao);
    glDeleteBuffers(1, &mVbo);
}

void SceneRenderer::renderScene(const Scene&      scene,
                                const fuse::Mat4& proj,
                                const fuse::Mat4& view) {
    glClearColor(.2f, .2f, .2f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const GLint viewLoc = glGetUniformLocation(mShaderProgram, "view");
    const GLint projLoc = glGetUniformLocation(mShaderProgram, "proj");
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE /*transpose*/, view.ptr());
    glUniformMatrix4fv(projLoc, 1, GL_TRUE /*transpose*/, proj.ptr());

    const auto& registry = scene.getRegistry();
    for (auto&& [entity, transform, mesh] : registry.view<fuse::CTransform, fuse::CMesh>().each()) {

        const auto translationMat = fuse::Mat4::CreateTranslation(transform.translation);
        const auto scaleMat       = fuse::Mat4::CreateScaling(transform.scale);
        const auto rotationMat    = fuse::Mat4::CreateRotationX(degrees(transform.rotation.x)) *
                                 fuse::Mat4::CreateRotationY(degrees(transform.rotation.y)) *
                                 fuse::Mat4::CreateRotationZ(degrees(transform.rotation.z));
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

} // namespace fuse
