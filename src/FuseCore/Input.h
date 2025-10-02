#pragma once
#include "Event.h"
#include "Keyboard.h"

namespace fuse {
class Event;

/// @brief Query the state of input device.
///
/// @note Internal only. The \p UpdateStates() function need to be called once per frame.
/// @note Internal only. The \p OnEvent() function need to be called once per frame.
/// @todo Add support for joystick / gamepad
class Input {
public:
    /// @name Keyboard
    /// @{

    /// @brief Query if the given key @b key has been pressed this frame.
    /// @param key The key to query.
    /// @return True if key @b key has been pressed this frame.
    static bool IsKeyPressed(ScanCode key) noexcept;

    /// @brief Query if the given key @b key is currently pressed.
    /// @param key The key to query.
    /// @return True if key @b key is currently pressed.
    static bool IsKeyDown(ScanCode key) noexcept;

    /// @brief Query if the given key @b key has been released this frame.
    /// @param key The key to query.
    /// @return True if key @b key has been released this frame.
    static bool IsKeyReleased(ScanCode key) noexcept;

    ///  @}

    /// @name Mouse
    /// @{

    /// @brief Query if the given mouse @b button has been pressed this frame.
    /// @param button The mouse button to query.
    /// @return True if the mouse button @b button has been pressed this frame.
    static bool IsButtonPressed(MouseButton button) noexcept;

    /// @brief Query if the given mouse @b button is currently pressed.
    /// @param button The mouse button to query.
    /// @return True if the mouse @b button is currently pressed.
    static bool IsButtonDown(MouseButton button) noexcept;

    /// @brief Query if the given mouse @b button has been released this frame.
    /// @param button The mouse button to query.
    /// @return True if the mouse @b button has been released this frame.
    static bool IsButtonReleased(MouseButton button) noexcept;

    /// @brief Return the mouse position in pixel coordinate.
    ///
    /// The top-left of the screen or window is at (0, 0).<br/>
    /// The bottom-right of the screen or window is at (width,height)
    /// @return The x and y position of the mouse in pixel.
    static std::pair<float, float> GetMousePosition() noexcept;

    /// @brief Return the current mouse position delta in pixel coordinates.
    ///
    /// The top-left of the screen or window is at (0, 0).<br/>
    /// The bottom-right of the screen or window is at (width,height).<br/>
    /// If no mouse movement happen during this frame, 0 is returned.
    /// @return The x and y delta position of the mouse in pixel.
    static std::pair<float, float> GetMousePositionDelta() noexcept;

    /// @brief Return the amount of mouse scroll (wheel) during this frame.
    ///
    /// Horizontal positive to the right and negative to the left.<br/>
    /// Vertical positive away from the user and negative toward the user.<br/>
    /// If no scroll happen during this frame, 0 is returned.
    /// @return The x and y scoll of the mouse.
    static std::pair<float, float> GetMouseScrollDelta() noexcept;

    ///  @}

    /// @name Internal
    ///  @{

    /// @brief Update the internal input state.
    ///        This must be called once per frame.
    /// @remark Internal only.
    static void UpdateStates() noexcept;

    /// @brief Update the states of the inputs.
    ///        This should be called during processing events.
    /// @param event The event to process.
    /// @remark Internal only.
    static void OnEvent(const Event& event) noexcept;

    ///  @}
};

} // namespace fuse
