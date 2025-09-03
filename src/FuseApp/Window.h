#pragma once
#include <optional>
#include <string>
#include <utility>

struct SDL_Cursor;
struct SDL_Surface; // NOLINT(readability-identifier-naming) WTF ? why only for SDL_Surface
struct SDL_Window;
struct SDL_GLContextState;

namespace fuse {


/// @brief Struct which hold windows create paramaters
struct WindowCreateInfo {
    std::string title     = "FuseEngine"; ///< The window title.
    int         width     = 1600;         ///< The window width.
    int         height    = 900;          ///< The window height.
    bool        resizable = true;         ///< Should the window be resizable by the user.
};

/// @brief Platform independent window
///
/// @todo void setKeyRepeateEnable(bool)
/// @todo void requestAttention()
class Window {
public:
    /// @brief Create a invalide window.
    Window() = default;

    /// @brief Construct a new winodws.
    /// @param info The window create info paramaters.
    Window(const WindowCreateInfo& info);

    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;

    /// @brief Move constructor.
    /// @todo  std::exchange
    Window(Window&&) noexcept;

    /// @brief Move assignement.
    /// @return
    /// @todo  std::exchange
    Window& operator=(Window&&) noexcept;

    /// @brief Destroy the window.
    /// Close the window and free all ressources.
    virtual ~Window();

    /// @brief Create or recreate the window.
    /// @param info The window create info paramaters.
    /// @return true if the window has been created oterwise, return false.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] bool create(const WindowCreateInfo& info = WindowCreateInfo());

    /// @brief Close the window.
    /// @warning This function should only be called on the main thread.
    void close();

    /// @brief Query if the window is open.
    /// @return true if the window is open otherwise, return false.
    [[nodiscard]] bool isOpen() const noexcept;

    /// @brief Request that the window be made as large as possible.
    /// Non-resizable windows can't be maximized.
    /// @warning This function should only be called on the main thread.
    /// @todo add more doc
    void maximize() noexcept;

    /// @brief Query if the window is maximized.
    /// @return ture if the window is maximized otherwise, return false.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] bool isMaximized() const noexcept;

    /// @brief Request that the window be minimized to an iconic representation.
    /// @warning This function should only be called on the main thread.
    /// @todo add more doc
    void minimize() noexcept;

    /// @brief Query if the window is minimized.
    /// @return ture if the window is minimized otherwise, return false.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] bool isMinimized() const noexcept;

    /// @brief Request that the size and position of a minimized or maximized window be restored.
    /// @warning This function should only be called on the main thread.
    /// @todo add more doc
    void restore() noexcept;

    /// @brief Change the window title.
    /// @param title The new title.
    /// @warning This function should only be called on the main thread.
    void setTitle(const std::string& title) noexcept;

    /// @brief Get the window title.
    /// @return The window title.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] std::string getTitle() const;

    /// @brief Set the user-resizable state of a window.
    /// @param resizable true to allow resizing, false to disallow.
    /// @warning This function should only be called on the main thread.
    /// @note This does not affect call to setSize().
    void setResizable(bool resizable) noexcept;

    /// @brief Query if the window is resizable by the user.
    /// @return true if the window is resizable by the user, otherwise false.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] bool isResizable() const noexcept;

    /// @brief Request that the window's position be set.
    /// @param x the x coordinate of the window.
    /// @param y the y coordinate of the window.
    /// @warning This function should only be called on the main thread.
    /// @todo add more doc
    void setPosition(int x, int y) noexcept;

    [[nodiscard]] std::pair<int, int> getPosition() const noexcept;

    /// @brief Change the window visibility.
    /// @param visible true to show the window, false to hide the window.
    /// @warning This function should only be called on the main thread.
    void setVisible(bool visible) noexcept;

    /// @brief Query if the window is visible.
    /// @return true if the window is visible, otherwise false.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] bool isVisible() const noexcept;

    /// @brief Request that the size of a window's client area be set.
    ///
    /// Request the operating system to resize the window to `width`x`height`.
    ///
    /// If the window is in a fullscreen or maximized state, this request has no effect.
    ///
    /// @param width  The new window width, must be > 0.
    /// @param height The new window height, must be > 0.
    /// @warning This function should only be called on the main thread.
    /// @note If the window size has changed, this will trigger a WindowResizeEvent.
    /// @todo add more doc
    void setSize(int width, int height) noexcept;

    /// @brief Get the size of a window's client area.
    /// @return The size of a window's client area.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] std::pair<int, int> getSize() const noexcept;

    /// @brief Set the maximum size of a window's client area.
    /// @param maxWidth the minimum width of the window, or 0 for no limit.
    /// @param maxHeight the minimum height of the window, or 0 for no limi
    /// @warning This function should only be called on the main thread.
    /// @todo add more doc
    void setMaximumSize(int maxWidth, int maxHeight) noexcept;

    /// @brief Set the minimum size of a window's client area.
    /// @param minWidth the minimum width of the window, or 0 for no limit.
    /// @param minHitdh the minimum height of the window, or 0 for no limit.
    /// @warning This function should only be called on the main thread.
    /// @todo add more doc
    void setMinimalSize(int minWidth, int minHeight) noexcept;

    /// @brief Change the window's icon.
    ///
    /// Set a new image as the window's icon from an array of RGBA pixel.
    /// @b pixels must be an array of size @b width x @ @b height x @b 4.
    ///
    /// If no icon is set, the OS default icon is used by default.
    ///
    /// @param width  The width of the icon.
    /// @param height The height of the icon.
    /// @param pixels Pointer to the array of pixels in memory.
    ///               The pixels are copied, so you need not keep the source alive after calling this function.
    /// @warning This function should only be called on the main thread.
    void setIcon(unsigned width, unsigned height, const unsigned* pixels) noexcept;

    /// @brief Set the window opacity.
    /// @param opacity The window opacity (0.0f - transparent, 1.0f - opaque).
    void setOpacity(float opacity) noexcept;

    /// @brief
    /// @param width
    /// @param height
    /// @param pixels
    /// @warning This function should only be called on the main thread.
    /// @bug     This currently set the cursor for each window.
    void setMouseCursor(unsigned width, unsigned height, const unsigned* pixels) noexcept;

    /// @brief Query if the window has input focus.
    /// @return True if the window has input focus, otherwise false.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] bool hasFocus() const noexcept;

    /// @brief Request that the input focus be given to the window.
    /// @warning This function should only be called on the main thread.
    void requestFocus() noexcept;

    /// @name Mouse visibility
    /// @{

    //void               setMouseVisible(bool visible);
    //[[nodiscard]] bool isMouseVisible() const;
    //[[nodiscard]] bool toogleMouseVisiblolity();

    /// @}

    /// @name Mouse capture
    /// @{

    //void captureMouse(bool capture);
    //void isMouseCaptured() const noexcept;
    //void toogleCaptureMouse();
    //void setMouseCaptureRect();
    //void getMouseCaptureRect() const noexcept;

    /// @}

    /// @name Mouse relative
    /// @{

    /// @brief Enable or disable relative mouse mode for this window.
    ///
    /// When mouse relative mode is enabled, the mouse cursor is hidden,
    /// and the mouse position is constrained to the window.
    /// The window will still receive mouse motion events when the mouse
    /// reaches the edges of the window.
    ///
    /// @param enable true to enable relative mouse mode, false to disable it.
    /// @warning This function should only be called on the main thread.
    void setMouseRelative(bool enable) noexcept;

    /// @brief Query whether relative mouse mode is enabled for a window.
    /// @return true if relative mouse mode is enabled, false otherwise.
    /// @warning This function should only be called on the main thread.
    [[nodiscard]] bool isMouseRelative() const noexcept;

    /// @brief Toggle relative mouse mode.
    /// @warning This function should only be called on the main thread.
    void toogleMouseRelative() noexcept;

    /// @}

    /// @brief Get the native handle of this window.
    ///
    /// - On Windows: HWND
    /// - On Linux:
    /// @return The platform handle.
    [[nodiscard]] void* getNativeHandle() const noexcept;

    [[nodiscard]] unsigned getId() const noexcept;

    [[nodiscard]] SDL_Window* getSDLWindow() const noexcept { return mWindow; }

    [[nodiscard]] SDL_GLContextState* getGLContext() const noexcept { return mGLContext; }

    /// @brief Retive a window from it's id.
    /// @param windowId The window id.
    /// @return A pointer to the window if found, otherwise return nullptr.
    [[nodiscard]] static std::optional<Window*> getWindowFromID(unsigned windowId);

protected:
    void onCreate() {}

    void onResize(int width, int height) {}

    void onFocusChanged(bool focusGained) {}

    void onMouseEnter() {}

    void onMouseLeaver() {}

    void onMouseButtonPressed() {}

    void onMouseButtonRelease() {}

private:
    SDL_Window*         mWindow{};      ///< The SDL window
    SDL_GLContextState* mGLContext{};   ///< The OpenGL context
    SDL_Surface*        mIconSurface{}; ///< The window icon
    SDL_Cursor*         mCursor{};      ///< The mouse cursor
};

} // namespace fuse


#if TODO
/// @brief Get the windows which currently have input focus.
std::optional<Window> getFocusWindow();
std::vector<Window>   getAllWindows();

std::optional<Event> pollEvent();
std::optional<Event> waitEvent();
std::optional<Event> peekEvent();

std::vectov<Monitor> getMonitors();
Monitor              getPrimaryMonitor();

struct VideoMode {
    int width;
    int height;
    int refreshRate;
};

struct Monitor {
    VideoMode              getCurrentVideoMode() const;
    std::vector<VideoMode> getSupportedVideoMode() const;
    std::string            getName() const;
}
#endif
