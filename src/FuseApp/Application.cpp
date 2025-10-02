#include "Application.h"

#include "SDL3/SDL3Helper.h"
#include "Window.h"

#include <FuseCore/fileSystem/FileSystem.h>
#include <FuseCore/Input.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <spdlog/spdlog.h>

namespace {
void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei /*length*/,
                                const GLchar* message,
                                const void* /*userParam*/) {
    std::string_view sourceToString = [](GLenum source) {
        switch (source) {
                // clang-format off
            case GL_DEBUG_SOURCE_API:             return "GL_DEBUG_SOURCE_API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY:     return "GL_DEBUG_SOURCE_THIRD_PARTY";
            case GL_DEBUG_SOURCE_APPLICATION:     return "GL_DEBUG_SOURCE_APPLICATION";
            case GL_DEBUG_SOURCE_OTHER:           return "GL_DEBUG_SOURCE_OTHER";
            default: return "Unknown";
                // clang-format on
        }
    }(source);

    std::string_view severityToString = [](GLenum severity) {
        switch (severity) {
                // clang-format off
            case GL_DEBUG_SEVERITY_HIGH:        return "GL_DEBUG_SEVERITY_HIGH";
            case GL_DEBUG_SEVERITY_MEDIUM:      return "GL_DEBUG_SEVERITY_MEDIUM";
            case GL_DEBUG_SEVERITY_LOW:         return "GL_DEBUG_SEVERITY_LOW";
            case GL_DEBUG_SEVERITY_NOTIFICATION:return "GL_DEBUG_SEVERITY_NOTIFICATION";
            default: return "Unknown";
                // clang-format on
        }
    }(severity);

    switch (type) {
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        case GL_DEBUG_TYPE_ERROR:
            spdlog::error("[{}] [{}] ({}) {}", sourceToString, severityToString, id, message);
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        case GL_DEBUG_TYPE_PORTABILITY:
        case GL_DEBUG_TYPE_PERFORMANCE:
            spdlog::warn("[{}] [{}] ({}) {}", sourceToString, severityToString, id, message);
            break;
        case GL_DEBUG_TYPE_MARKER:
        case GL_DEBUG_TYPE_PUSH_GROUP:
        case GL_DEBUG_TYPE_POP_GROUP:
        case GL_DEBUG_TYPE_OTHER:
        default:
            spdlog::info("[{}] [{}] ({}) {}", sourceToString, severityToString, id, message);
            break;
    }
}

} // namespace

namespace fuse {

Application::Application() = default;

Application::~Application() = default;

bool Application::init() {

    const int compiled = SDL_VERSION;      /* hardcoded number from SDL headers */
    const int linked   = SDL_GetVersion(); /* reported by linked SDL library */
    spdlog::info("SDL    version {}.{}.{} (compiled)",
                 SDL_VERSIONNUM_MAJOR(compiled),
                 SDL_VERSIONNUM_MINOR(compiled),
                 SDL_VERSIONNUM_MICRO(compiled));
    spdlog::info("SDL    version {}.{}.{} (linked)",
                 SDL_VERSIONNUM_MAJOR(linked),
                 SDL_VERSIONNUM_MINOR(linked),
                 SDL_VERSIONNUM_MICRO(linked));
    spdlog::info("spdlog version {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    spdlog::info("NumVideoDrivers {}", SDL_GetNumVideoDrivers());
    for (auto i = 0; i < SDL_GetNumVideoDrivers(); i++) {
        spdlog::info(" - {}", SDL_GetVideoDriver(i));
    }

    spdlog::info("NumAudioDrivers {}", SDL_GetNumAudioDrivers());
    for (auto i = 0; i < SDL_GetNumAudioDrivers(); i++) {
        spdlog::info(" - {}", SDL_GetAudioDriver(i));
    }

    spdlog::info("NumRenderDrivers {}", SDL_GetNumRenderDrivers());
    for (auto i = 0; i < SDL_GetNumRenderDrivers(); i++) {
        spdlog::info(" - {}", SDL_GetRenderDriver(i));
    }

    spdlog::info("NumGPUDrivers {}", SDL_GetNumGPUDrivers());
    for (auto i = 0; i < SDL_GetNumGPUDrivers(); i++) {
        spdlog::info(" - {}", SDL_GetGPUDriver(i));
    }

    // SDL_SetHint(SDL_HINT_QUIT_ON_LAST_WINDOW_CLOSE , "1")
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD)) {
        spdlog::error("Fail to init SDL3: {}", SDL_GetError());
        return false;
    }

    mMainWindow = std::make_unique<Window>();
    if (!mMainWindow->create()) {
        return false;
    }

    // does not work on WSL ?
    //mMainWindow->setPosition(0, 0);
    //mMainWindow->setOpacity(0.1f);

    // Set default icon
    // TODO: Can we generate at compile time ?
    {
        constexpr unsigned kIconWith   = 32;
        constexpr unsigned kIconHeight = 32;
        unsigned char      buffer[kIconWith * kIconWith * 4];
        for (unsigned row = 0; row < kIconHeight; row++) {
            for (unsigned col = 0; col < kIconWith; col++) {
                const unsigned i = row * kIconHeight * 4 + col * 4;
                if (col == 7 || row == 7) {
                    buffer[i + 0] = 255;
                    buffer[i + 1] = 0;
                    buffer[i + 2] = 0;
                    buffer[i + 3] = 255;
                } else {
                    buffer[i + 0] = 0;
                    buffer[i + 1] = 0;
                    buffer[i + 2] = 0;
                    buffer[i + 3] = 0;
                }
            }
        }
        mMainWindow->setIcon(kIconWith, kIconHeight, reinterpret_cast<unsigned int*>(&buffer));
    }


    //mMainWindow2 = std::make_unique<Window>();
    //if (!mMainWindow2->create(WindowCreateInfo{.title = "Windows 2"})) {
    //    return false;
    //};


    //Use Vsync
    if (!SDL_GL_SetSwapInterval(1)) {
        spdlog::error("Warning: Unable to set VSync! SDL Error: {}\n", SDL_GetError());
    }

    // Load GL extensions using glad
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) == 0) {
        spdlog::error("Failed to initialize the OpenGL context.\n");
        return false;
    }

    GLint major{};
    GLint minor{};
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    spdlog::info("Using OpenGL: {}.{}", major, minor);
    spdlog::info(" - Vendor:         {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    spdlog::info(" - Renderer:       {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    spdlog::info(" - Shader version: {}",
                 reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));


    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, nullptr /*userdata*/);
    glDebugMessageControl(GL_DONT_CARE,
                          GL_DONT_CARE,
                          GL_DEBUG_SEVERITY_NOTIFICATION,
                          0,
                          nullptr,
                          GL_FALSE);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    // load main font
    {
        const auto fontPath = FileSystem::GetExecutableDirectory() / "fonts/Roboto-Regular.ttf";
        if (!std::filesystem::exists(fontPath)) {
            spdlog::warn("Font not found: {}. Fallback to default font.", fontPath.string());
            io.Fonts->AddFontDefault();
        } else {
            if (io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 13) == nullptr) {
                spdlog::warn("Fail to load font: {}. Fallback to default font.", fontPath.string());
                io.Fonts->AddFontDefault();
            }
        }
    }

    // load icon
    {
        ImFontConfig fontConfig{};
        fontConfig.MergeMode            = true;
        fontConfig.FontDataOwnedByAtlas = false;
        const auto fontPath =
          FileSystem::GetExecutableDirectory() / "fonts/materialdesignicons-webfont.ttf";
        if (!std::filesystem::exists(fontPath)) {
            spdlog::error("Font not found: {}.", fontPath.string());
        } else if (io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(),
                                                0.0f /*size_pixels*/,
                                                &fontConfig,
                                                nullptr /*glyph_ranges*/) == nullptr) {
            spdlog::error("Fail to load font: {}.", fontPath.string());
        }
    }

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    if (!ImGui_ImplSDL3_InitForOpenGL(mMainWindow->getSDLWindow(), mMainWindow->getGLContext())) {
    }
    if (!ImGui_ImplOpenGL3_Init("#version 130")) {
    }

    return onInit();
}

bool Application::shutdown() {
    onShutdown();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    mMainWindow.reset();
    SDL_Quit();
    return true;
}

void Application::run() {
    if (!init()) {
        return;
    }

    mTimer.reset();
    while (mIsRunning) {
        SDL_Event sdlEvent{};
        while (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_EVENT_QUIT) {
                mIsRunning = false;
                break;
            }

            // pass event to imgui
            ImGui_ImplSDL3_ProcessEvent(&sdlEvent);

            if (const auto result = fuse::sdl3::ConvertEvent(sdlEvent)) {
                const Event& event = result.value();


                const bool isKeyEvent =
                  event.isA<KeyPressedEvent>() || event.isA<KeyReleasedEvent>();
                const bool isMouseEvent =
                  event.isA<MouseButtonEvent>() || event.isA<MouseMovedEvent>();

                // skip mouse event if ImGui want the mouse.
                // skip keyboard event if ImGui want the keyboard.
                if ((isKeyEvent || isMouseEvent) &&
                    (ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantCaptureMouse)) {
                    continue;
                }

                // update the inputs and dispatch the event to subclass.
                Input::OnEvent(event);
                onEvent(event);
            }
        }
        mTimer.tick();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        //spdlog::info("{}x{}", mMainWindow->getSize().first, mMainWindow->getSize().second);
        onImGui();
        onUpdate(mTimer.deltaTime());
        Input::UpdateStates();

        // Rendering
        ImGui::Render();
        const ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ==
            ImGuiConfigFlags_ViewportsEnable) {
            SDL_Window*   backupCurrentWindow  = SDL_GL_GetCurrentWindow();
            SDL_GLContext backupCurrentContext = SDL_GL_GetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            SDL_GL_MakeCurrent(backupCurrentWindow, backupCurrentContext);
        }

        SDL_GL_SwapWindow(mMainWindow->getSDLWindow());
        //SDL_GL_SwapWindow(mMainWindow2->getSDLWindow());
    }

    shutdown();
}

void Application::onEvent(const Event& event) {
    if (const auto* keyEvent = event.getIf<KeyPressedEvent>()) {
        if (keyEvent->getScanCode() == fuse::ScanCode::P) {
            mTimer.stop();
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::O) {
            mTimer.start();
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::I) {
            mTimer.reset();
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::F1) {
            //mMainWindow->toggleGrabInput();
        }
        if (keyEvent->getScanCode() == fuse::ScanCode::F2) {
            mMainWindow->toggleMouseRelative();
        }
    }
}

} // namespace fuse
