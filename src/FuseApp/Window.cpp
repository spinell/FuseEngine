#include "Window.h"

#include "SDL3/SDL3Error.h"

#include <SDL3/SDL.h>

namespace {
/// Key to store the pointer to the Window class in the SDL_Window user data.
constexpr const char* kWindowUserDataKey = "FuseSDLWindow";
} // namespace

namespace fuse {

Window::~Window() { close(); }

bool Window::create(const WindowCreateInfo& info) {
    close();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    SDL_WindowFlags windowFlags = 0;
    if (info.resizable) {
        windowFlags |= SDL_WINDOW_RESIZABLE;
    }

    //windowFlags |= SDL_WINDOW_FULLSCREEN;
    windowFlags |= SDL_WINDOW_OPENGL;
    //windowFlags |= SDL_WINDOW_HIDDEN;
    //windowFlags |= SDL_WINDOW_TRANSPARENT;

    //windowFlags |= SDL_WINDOW_KEYBOARD_GRABBED;
    //windowFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
    //windowFlags |= SDL_WINDOW_MOUSE_CAPTURE;
    mWindow = SDL_CreateWindow(info.title.c_str(), info.width, info.height, windowFlags);
    if (!mWindow) {
        fuse::sdl3::CheckSDLError("SDL_CreateWindow");
        return false;
    }

    const auto props = SDL_GetWindowProperties(mWindow);
    if (!SDL_SetPointerProperty(props, kWindowUserDataKey, this)) {
        fuse::sdl3::CheckSDLError("SDL_SetPointerProperty");
    }

    mGLContext = SDL_GL_CreateContext(mWindow);
    if (!mGLContext) {
        fuse::sdl3::CheckSDLError("SDL_GL_CreateContext");
        return false;
    }

    // This function will enable text input (SDL_EVENT_TEXT_INPUT and SDL_EVENT_TEXT_EDITING events)
    // in the specified window. Please use this function paired with SDL_StopTextInput().
    // Text input events are not received by default.
    // On some platforms using this function shows the screen keyboard and/or activates an IME,
    // which can prevent some key press events from being passed through.
    if (!SDL_StartTextInput(mWindow)) {
        fuse::sdl3::CheckSDLError("SDL_StartTextInput");
        return false;
    }

    return true;
}

void Window::close() {
    SDL_DestroySurface(mIconSurface);
    SDL_DestroyCursor(mCursor);
    SDL_DestroyWindow(mWindow);
}

bool Window::isOpen() const noexcept { return mWindow != nullptr; }

void Window::maximize() noexcept {
    if (!SDL_MaximizeWindow(mWindow)) {
        fuse::sdl3::CheckSDLError("SDL_MaximizeWindow");
    }
}

void Window::minimize() noexcept {
    if (!SDL_MinimizeWindow(mWindow)) {
        fuse::sdl3::CheckSDLError("SDL_MinimizeWindow");
    }
}

bool Window::isMaximized() const noexcept {
    return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MINIMIZED;
}

bool Window::isMinimized() const noexcept {
    return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MINIMIZED;
}

void Window::restore() noexcept {
    if (!SDL_RestoreWindow(mWindow)) {
        fuse::sdl3::CheckSDLError("SDL_RestoreWindow");
    }
}

void Window::setSize(int width, int height) noexcept {
    if (!SDL_SetWindowSize(mWindow, width, height)) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowSize");
    }
}

std::pair<int, int> Window::getSize() const noexcept {
    int width  = 0;
    int height = 0;
    if (!SDL_GetWindowSize(mWindow, &width, &height)) {
        fuse::sdl3::CheckSDLError("SDL_GetWindowSize");
    }
    return {width, height};
}

void Window::setMaximumSize(int maxWidth, int maxHeight) noexcept {
    if (!SDL_SetWindowMaximumSize(mWindow, maxWidth, maxHeight)) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowMaximumSize");
    }
}

void Window::setMinimalSize(int minWidth, int minHeight) noexcept {
    if (!SDL_SetWindowMinimumSize(mWindow, minWidth, minHeight)) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowMinimumSize");
    }
}

void Window::setResizable(bool resizable) noexcept {
    if (!SDL_SetWindowResizable(mWindow, resizable)) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowResizable");
    }
}

bool Window::isResizable() const noexcept {
    return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_RESIZABLE;
}

void Window::setPosition(int x, int y) noexcept {
    if (!SDL_SetWindowPosition(mWindow, x, y)) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowPosition");
    }
}

std::pair<int, int> Window::getPosition() const noexcept {
    int x = 0;
    int y = 0;
    if (!SDL_GetWindowPosition(mWindow, &x, &y)) {
        fuse::sdl3::CheckSDLError("SDL_GetWindowPosition");
    }
    return {x, y};
}

void Window::setTitle(const std::string& title) noexcept {
    if (!SDL_SetWindowTitle(mWindow, title.data())) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowTitle");
    }
}

std::string Window::getTitle() const { return SDL_GetWindowTitle(mWindow); }

void Window::setVisible(bool visible) noexcept {
    if (visible) {
        if (!SDL_ShowWindow(mWindow)) {
            fuse::sdl3::CheckSDLError("SDL_ShowWindow");
        }
    } else {
        if (!SDL_HideWindow(mWindow)) {
            fuse::sdl3::CheckSDLError("SDL_HideWindow");
        }
    }
}

bool Window::isVisible() const noexcept {
    return !(SDL_GetWindowFlags(mWindow) & SDL_WINDOW_HIDDEN);
}

void Window::setIcon(unsigned width, unsigned height, const unsigned* pixels) noexcept {
    SDL_DestroySurface(mIconSurface);

    const auto pixelFormat =
      SDL_GetPixelFormatForMasks(32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    mIconSurface = SDL_CreateSurfaceFrom(static_cast<int>(width),
                                         static_cast<int>(height),
                                         pixelFormat,
                                         static_cast<void*>(const_cast<unsigned*>(pixels)),
                                         static_cast<int>(width) * 4);

    if (!mIconSurface) {
        fuse::sdl3::CheckSDLError("SDL_CreateSurfaceFrom");
    }

    if (!SDL_SetWindowIcon(mWindow, mIconSurface)) {
        fuse::sdl3::CheckSDLError("SDL_CreateSurfaceFrom");
    }
}

void Window::setOpacity(float opacity) noexcept {
    if (!SDL_SetWindowOpacity(mWindow, opacity)) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowOpacity");
    }
}

void Window::setMouseCursor(unsigned width, unsigned height, const unsigned* pixels) noexcept {
    SDL_DestroyCursor(mCursor);

    const auto pixelFormat =
      SDL_GetPixelFormatForMasks(32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    SDL_Surface* curorSurface =
      SDL_CreateSurfaceFrom(static_cast<int>(width),
                            static_cast<int>(height),
                            pixelFormat,
                            static_cast<void*>(const_cast<unsigned*>(pixels)),
                            static_cast<int>(width) * 4);

    mCursor = SDL_CreateColorCursor(curorSurface, 10, 10);
    if (!mCursor) {
        fuse::sdl3::CheckSDLError("SDL_SetCursor");
    }

    SDL_DestroySurface(curorSurface);

    if (!SDL_SetCursor(mCursor)) {
        fuse::sdl3::CheckSDLError("SDL_SetCursor");
    }
}

bool Window::hasFocus() const noexcept {
    return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_INPUT_FOCUS;
}

void Window::requestFocus() noexcept {
    if (!SDL_RaiseWindow(mWindow)) {
        fuse::sdl3::CheckSDLError("SDL_RaiseWindow");
    }
}

void Window::toogleMouseRelative() noexcept {
    const bool isRelative = SDL_GetWindowRelativeMouseMode(mWindow);
    setMouseRelative(!isRelative);
}

void Window::setMouseRelative(bool enable) noexcept {
    if (!SDL_SetWindowRelativeMouseMode(mWindow, enable)) {
        fuse::sdl3::CheckSDLError("SDL_SetWindowRelativeMouseMode");
    }
}

bool Window::isMouseRelative() const noexcept { return SDL_GetWindowRelativeMouseMode(mWindow); }

void* Window::getNativeHandle() const noexcept {
    void* windowHandle = nullptr;

    if (mWindow) {
#if defined(SDL_PLATFORM_WIN32)
        windowHandle = SDL_GetPointerProperty(SDL_GetWindowProperties(mWindow),
                                              SDL_PROP_WINDOW_WIN32_HWND_POINTER,
                                              nullptr);
#elif defined(SDL_PLATFORM_LINUX)
        //if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0) {
        //    return nullptr; // TODO
        //} else if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {
        //    return nullptr; // TODO
        //}
#endif
    }
    return windowHandle;
}

unsigned Window::getId() const noexcept { return SDL_GetWindowID(mWindow); }

std::optional<Window*> Window::getWindowFromID(unsigned windowId) {
    SDL_Window* window = SDL_GetWindowFromID(windowId);
    if (window) {
        const auto props = SDL_GetWindowProperties(window);
        auto*      win   = SDL_GetPointerProperty(props, kWindowUserDataKey, nullptr);
        if (win) {
            return static_cast<Window*>(win);
        }
    }
    return {};
}

} // namespace fuse
