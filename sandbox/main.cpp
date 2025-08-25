#include "Camera.h"
#include "Timer.h"

#include <FuseCore/math/Angle.h>
#include <FuseCore/math/Mat4.h>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <print>

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

int main() {
    Camera camera;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    fuse::GameTimer timer;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    const SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window*           window = SDL_CreateWindow("FuseEngine Sandbox", 800, 600, windowFlags);
    if (!window) {
        std::println("Failed to create SDL window: {}", SDL_GetError());
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::println("Failed to create OpenGL Context: {}", SDL_GetError());
        return -1;
    }

    //Use Vsync
    if (!SDL_GL_SetSwapInterval(1)) {
        std::println("Warning: Unable to set VSync! SDL Error: {}\n", SDL_GetError());
    }

    // Load GL extensions using glad
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::println("Failed to initialize the OpenGL context.\n");
        return -1;
    }

    unsigned int vertexShader = 0;
    vertexShader              = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &kVertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int  success{};
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n {}\n", infoLog);
    }

    unsigned int fragmentShader = 0;
    fragmentShader              = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &kFragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::println("ERROR::SHADER::PIXEL::COMPILATION_FAILED\n {}\n", infoLog);
    }

    unsigned int shaderProgram = 0;
    shaderProgram              = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::println("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n {}\n", infoLog);
    }
    glUseProgram(shaderProgram);

    unsigned int vbo = 0;
    glGenBuffers(1, &vbo);

    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(20));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    bool done = false;
    timer.reset();
    while (!done) {
        SDL_Event event{};
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                auto& windowEvent = event.window;
                glViewport(0, 0, windowEvent.data1, windowEvent.data2);
                camera.setAspectRatio((float)windowEvent.data1 / (float)windowEvent.data2);
            }
            if (event.type == SDL_EVENT_MOUSE_MOTION) {
                auto& motionEvent = event.motion;
                // Make each pixel correspond to a 1/8 of a degree.
                auto dx = fuse::degrees(0.125f) * motionEvent.xrel; // rotation around local Up
                auto dy = fuse::degrees(0.125f) * motionEvent.yrel; // rotation around local right
                camera.pitch(-dy);
                camera.yaw(-dx);
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                auto& keyEvent = event.key;
                if (keyEvent.key == SDLK_A) {
                    auto pos = camera.getPosition();
                    pos -= camera.getRight() * 2;
                    camera.setPosition(pos);
                }
                if (keyEvent.key == SDLK_D) {
                    auto pos = camera.getPosition();
                    pos += camera.getRight() * 2;
                    camera.setPosition(pos);
                }
                if (keyEvent.key == SDLK_W) {
                    auto pos = camera.getPosition();
                    pos += camera.getDirection() * 2;
                    camera.setPosition(pos);
                }
                if (keyEvent.key == SDLK_S) {
                    auto pos = camera.getPosition();
                    pos -= camera.getDirection() * 2;
                    camera.setPosition(pos);
                }
                if (keyEvent.key == SDLK_Q) {
                    auto pos = camera.getPosition();
                    pos += fuse::Vec3::kAxisY;
                    camera.setPosition(pos);
                }
                if (keyEvent.key == SDLK_E) {
                    auto pos = camera.getPosition();
                    pos += fuse::Vec3::kAxisYNeg;
                    camera.setPosition(pos);
                }
                if (keyEvent.key == SDLK_P) {
                    timer.stop();
                }
                if (keyEvent.key == SDLK_O) {
                    timer.start();
                }
                if (keyEvent.key == SDLK_I) {
                    timer.reset();
                }
            }
        }
        timer.tick();

        glClearColor(.2, .2, .2, 1);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const fuse::Mat4 translation = fuse::Mat4::CreateTranslation({0, 0, -11});
        const fuse::Mat4 scale       = fuse::Mat4::CreateScaling({1, 1, 1});
        const fuse::Mat4 rotation =
          fuse::Mat4::CreateRotation(fuse::degrees(10.0f) * timer.totalTime(), fuse::Vec3(1, 1, 0));
        fuse::Mat4  transform    = translation * rotation * scale;
        const GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_TRUE /*transpose*/, transform.ptr());

        //
        // update camera
        //
        fuse::Mat4  proj    = camera.getProjMatrix();
        fuse::Mat4  view    = camera.getViewMatrix();
        const GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_TRUE /*transpose*/, view.ptr());

        const GLint projLoc = glGetUniformLocation(shaderProgram, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_TRUE /*transpose*/, proj.ptr());

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        SDL_GL_SwapWindow(window);


        std::println("total {} elapsed {}", timer.totalTime(), timer.deltaTime());
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
