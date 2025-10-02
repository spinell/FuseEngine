#pragma once
#include "Keyboard.h"

#include <functional>
#include <string>
#include <variant>

namespace fuse {

//////////////////////////////////////////////////////////////////
///                      Windows Event
//////////////////////////////////////////////////////////////////

/// @brief
struct WindowCloseEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowCloseEvent";
    }
};

/// @brief
struct WindowDisplayChangedEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowDisplayChangedEvent";
    }
};

/// @brief
struct WindowMouseEnterEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowMouseEnterEvent";
    }
};

/// @brief
struct WindowMouseLeaveEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowMouseLeaveEvent";
    }
};

/// @brief
struct WindowFocusGainEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowFocusGainEvent";
    }
};

/// @brief
struct WindowFocusLostEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowFocusLostEvent";
    }
};

/// @brief Event triggered when the window enter the fullscreen mode.
struct WindowFullScreenEnterEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowFullScreenEnterEvent";
    }
};

/// @brief Event triggered when the window leave the fullscreen mode.
struct WindowFullScreenLeaveEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowFullScreenLeaveEvent";
    }
};

/// @brief Event triggered when the window has been moved.
class WindowMovedEvent {
public:
    WindowMovedEvent(int x, int y) noexcept
        : mPosX(x)
        , mPosY(y) {}

    [[nodiscard]] std::string toString() const;

private:
    int mPosX{};
    int mPosY{};
};

/// @brief
struct WindowMaximizedEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowMaximizedEvent";
    }
};

/// @brief
struct WindowMinimizedEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowMinimizedEvent";
    }
};

/// @brief Event triggered when the window has been resized.
class WindowResizedEvent {
public:
    WindowResizedEvent(int width, int height) noexcept
        : mWidth(width)
        , mHeight(height) {}

    [[nodiscard]] int getWidth() const noexcept { return mWidth; }

    [[nodiscard]] int getHeight() const noexcept { return mHeight; }

    [[nodiscard]] std::string toString() const;

private:
    int mWidth{};
    int mHeight{};
};

/// @brief
struct WindowRestoredEvent {
    [[nodiscard]] std::string toString() // NOLINT(readability-convert-member-functions-to-static)
      const {
        return "WindowRestoredEvent";
    }
};

//////////////////////////////////////////////////////////////////
///                      Mouse Event
//////////////////////////////////////////////////////////////////


/// @brief Event triggered when a mouse button has been pressed or released.
class MouseButtonEvent {
public:
    /// @brief
    /// @param button
    /// @param isPressed
    /// @param click
    /// @param mouseX
    /// @param mouseY
    MouseButtonEvent(
      MouseButton button, bool isPressed, unsigned click, float mouseX, float mouseY) noexcept
        : mButton(button)
        , mIsPressed(isPressed)
        , mClick(click)
        , mMouseX(mouseX)
        , mMouseY(mouseY) {}

    /// @brief Check if the button was pressed or released.
    /// @return True if the button was pressed otherwise, false.
    [[nodiscard]] bool isPressed() const noexcept { return mIsPressed; }

    /// @brief Get the button which trigger this event.
    /// @return The button which trigger this event.
    [[nodiscard]] MouseButton getButton() const noexcept { return mButton; }

    /// @brief Get the position of the mouse.
    /// @return The position of the mouse.
    [[nodiscard]] std::pair<float, float> getMousePos() const noexcept {
        return {mMouseX, mMouseY};
    }

    /// @brief Get the X position of the mouse.
    /// @return The X position of the mouse.
    [[nodiscard]] float getMousePosX() const noexcept { return mMouseX; }

    /// @brief Get the Y position of the mouse.
    /// @return The Y position of the mouse.
    [[nodiscard]] float getMousePosY() const noexcept { return mMouseY; }

    [[nodiscard]] std::string toString() const;

private:
    MouseButton mButton{};    //!
    bool        mIsPressed{}; //!
    unsigned    mClick{};     //!
    float       mMouseX{};    //!
    float       mMouseY{};    //!
};

/// @brief Event triggered when the mouse has moved.
class MouseMovedEvent {
public:
    /// @brief Construct a MouseMovedEvent.
    /// @param x The X coordinate, relative to window.
    /// @param y The Y coordinate, relative to window.
    /// @param deltaX The relative motion in the X direction.
    /// @param deltaY The relative motion in the Y direction.
    /// @param buttonMask The state of all mouse buttons.
    MouseMovedEvent(float x, float y, float deltaX, float deltaY, MouseButtonMask buttonMask)
        : mPosX{x}
        , mPosY{y}
        , mDeltaX{deltaX}
        , mDeltaY{deltaY}
        , mButtonState{buttonMask} {}

    /// @brief Get the mouse position relative to the window.
    /// @return The mouse x,y position relative to the window.
    [[nodiscard]] std::pair<float, float> getMousePosition() const { return {mPosX, mPosY}; }

    /// @brief Get the mouse motion.
    /// @return The mouse x,y motion.
    [[nodiscard]] std::pair<float, float> getMouseDelta() const { return {mDeltaX, mDeltaY}; }

    [[nodiscard]] std::string toString() const;

private:
    float           mPosX{};      //! The X coordinate, relative to window.
    float           mPosY{};      //! The Y coordinate, relative to window.
    float           mDeltaX{};    //! The relative motion in the X direction.
    float           mDeltaY{};    //! The relative motion in the Y direction.
    MouseButtonMask mButtonState; //! The state of all mouse button.
};

/// @brief Event triggered when the mouse wheel has moved.
class MouseScrolledEvent {
public:
    /// @brief  Construct a MouseScrolledEvent.
    /// @param deltaX The amount of horizontally scroll.
    /// @param deltaY The amount of vertical scroll.
    /// @param mouseX The mouse X coordinate, relative to window.
    /// @param mouseY The mouse Y coordinate, relative to window.
    MouseScrolledEvent(float deltaX, float deltaY, float mouseX, float mouseY) noexcept
        : mDeltaX{deltaX}
        , mDeltaY{deltaY}
        , mMouseX{mouseX}
        , mMouseY{mouseY} {}

    /// @brief Return the amount scrolled horizontally and vertically.
    ///        Horizontal positive to the right and negative to the left.
    ///        Vertical positive away from the user and negative toward the user
    [[nodiscard]] std::pair<float, float> getDelta() const noexcept { return {mDeltaX, mDeltaY}; }

    /// @brief Return the amount scrolled horizontally, positive to the right
    ///        and negative to the left.
    [[nodiscard]] float getDeltaX() const noexcept { return mDeltaX; }

    /// @brief Return the amount scrolled vertically, positive away from the user
    ///        and negative toward the user
    [[nodiscard]] float getDeltaY() const noexcept { return mDeltaY; }

    [[nodiscard]] std::string toString() const;

private:
    float mDeltaX{}; //! The amount of horizontally scroll.
    float mDeltaY{}; //! The amount of vertical scroll.
    float mMouseX{}; //! The mouse X coordinate, relative to window.
    float mMouseY{}; //! The mouse Y coordinate, relative to window.
};

//////////////////////////////////////////////////////////////////
///                    Keyboard Event
//////////////////////////////////////////////////////////////////


/// @brief Event triggered when a key was pressed.
class KeyPressedEvent {
public:
    KeyPressedEvent(ScanCode scancode, KeyCode key, bool isRepeated, KeyModMask modifier)
        : mKeyCode(key)
        , mScanCode(scancode)
        , mIsRepeated{isRepeated}
        , mModifier{modifier} {}

    [[nodiscard]] KeyCode getKeyCode() const noexcept { return mKeyCode; }

    [[nodiscard]] ScanCode getScanCode() const noexcept { return mScanCode; }

    [[nodiscard]] bool isRepeated() const noexcept { return mIsRepeated; }

    [[nodiscard]] bool isShift() const noexcept {
        return mModifier.isAnySet(KeyModFlag::LeftShift, KeyModFlag::RightShift);
    }

    [[nodiscard]] bool isLeftShift() const noexcept {
        return mModifier.isSet(KeyModFlag::LeftShift);
    }

    [[nodiscard]] bool isRightShift() const noexcept {
        return mModifier.isSet(KeyModFlag::RightShift);
    }

    [[nodiscard]] std::string toString() const;

private:
    KeyCode    mKeyCode{};
    ScanCode   mScanCode{};
    bool       mIsRepeated{};
    KeyModMask mModifier;
};

/// @brief Event triggered when a key was pressed.
class KeyReleasedEvent {
public:
    KeyReleasedEvent(ScanCode scancode, KeyCode key, KeyModMask modifier)
        : mKeyCode(key)
        , mScanCode(scancode)
        , mModifier{modifier} {}

    [[nodiscard]] KeyCode getKeyCode() const noexcept { return mKeyCode; }

    [[nodiscard]] ScanCode getScanCode() const noexcept { return mScanCode; }

    [[nodiscard]] bool isShift() const noexcept {
        return mModifier.isAnySet(KeyModFlag::LeftShift, KeyModFlag::RightShift);
    }

    [[nodiscard]] bool isLeftShift() const noexcept {
        return mModifier.isSet(KeyModFlag::LeftShift);
    }

    [[nodiscard]] bool isRightShift() const noexcept {
        return mModifier.isSet(KeyModFlag::RightShift);
    }

    [[nodiscard]] std::string toString() const;

private:
    KeyCode    mKeyCode{};
    ScanCode   mScanCode{};
    KeyModMask mModifier;
};

class TextInputEvent {
public:
    TextInputEvent(const char* text)
        : mText(text) {}

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    [[nodiscard]] std::string toString() const;

private:
    const char* mText{};
};

template <typename... Ts>
struct OverloadSet : Ts... {
    using Ts::operator()...;
};

/// @brief The requirement for a event type hold in \p Event.
template <typename T>
concept EventRequirement = requires(T t) {
    { t.toString() } -> std::convertible_to<std::string>;
};

/// @brief
class Event {
public:
    /// @brief Construct a event from the real event type.
    ///
    /// @tparam T The type of the event.
    /// @param  e The event itself.
    template <class T>
    Event(T e)
        : mData(e) {
        //static_assert(isValidEventType<T>, "T is not defined as a event in std::variant<> list.");
    }

    /// @brief Check if the underlying event is a specific type.
    /// @tparam T The event type to check.
    /// @return Return true if the underlying event type is \p T.
    template <EventRequirement T>
    [[nodiscard]] bool isA() const noexcept {
        //static_assert(isValidEventType<T>, "T is not defined as a event in std::variant<> list.");
        return std::holds_alternative<T>(mData);
    }

    /// @brief Return the underlying event.
    /// @tparam T The event type to return.
    /// @return Return a pointer on the underlying event or null if the event type is not \p T.
    template <EventRequirement T>
    [[nodiscard]] const T* getIf() const {
        //static_assert(isValidEventType<T>, "T is not defined as a event in std::variant<> list.");
        return std::get_if<T>(&mData);
    }

    /// @brief
    /// @tparam T
    /// @param callback
    template <EventRequirement T>
    void dispatch(std::function<void(const T&)> callback) const noexcept {
        if (isA<T>() && callback) {
            callback(std::get<T>(mData));
        }
    }

    /// @brief
    /// @param  handlers A variadic list of callables that take a specific event as their only parameter
    template <class... Handlers>
    void dispatch2(Handlers&&... handlers) const noexcept {
        OverloadSet overloadSet{std::forward<Handlers>(handlers)...,
                                []<typename T>(const T&) { /* ignore */ }};
        visit(overloadSet);
    }

    /// @brief Return a string that represent the event (Usefull for debugging).
    [[nodiscard]] std::string toString() const {
        auto visitor = []<typename T>(const T& event) { return event.toString(); };
        return std::visit(visitor, mData);
    }

private:
    std::variant<
      // Windows event
      WindowCloseEvent,
      WindowDisplayChangedEvent,
      WindowMouseEnterEvent,
      WindowMouseLeaveEvent,
      WindowFocusGainEvent,
      WindowFocusLostEvent,
      WindowFullScreenEnterEvent,
      WindowFullScreenLeaveEvent,
      WindowMovedEvent,
      WindowMaximizedEvent,
      WindowMinimizedEvent,
      WindowResizedEvent,
      WindowRestoredEvent,
      // Mouse event
      MouseButtonEvent,
      MouseMovedEvent,
      MouseScrolledEvent,
      // Key event
      KeyPressedEvent,
      KeyReleasedEvent,
      // Text input event
      TextInputEvent>
      mData;

    template <typename T>
    decltype(auto) visit(T&& visitor) const {
        return std::visit(std::forward<T>(visitor), mData);
    }
};

} // namespace fuse
