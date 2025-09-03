#pragma once
#include <FuseApp/Event.h>
#include <FuseApp/Keyboard.h>

#include <SDL3/SDL.h>

#include <optional>
#include <string>
#include <string_view>

namespace fuse::sdl3 {

/// @brief Convert SDL3 mouse button to fuse::MouseButton.
/// @param  button A SDL3 mouse button (SDL_BUTTON_LEFT, SDL_BUTTON_X1, ...).
/// @return        The converted mouse button or \p MouseButton::Unknown if the button is not suppported.
[[nodiscard]] MouseButton ConvertMouseButton(int button) noexcept;

/// @brief Convert a SDL scancode to fuse::ScanCode.
/// @param scancode The scancode to convert.
/// @return The converted scancode or \p KeyCode::Unknown if the key is not suppported.
[[nodiscard]] ScanCode ConvertScanCode(SDL_Scancode scancode) noexcept;

/// @brief Convert a SDL mouse button mask to fuse::MouseButtonMask.
/// @param buttonMask The SDL mouse button mask to convert.
/// @return The converted mouse button mask.
[[nodiscard]] MouseButtonMask ConvertMouseButtonMask(SDL_MouseButtonFlags buttonMask) noexcept;

/// @brief Convert a SDL key modifier mask to fuse::KeyModMask.
/// @param keymod The SDL key modifier mask to convert.
/// @return The converted key modifier mask.
[[nodiscard]] KeyModMask ConvertKeyModifierMask(SDL_Keymod keymod) noexcept;

[[nodiscard]] std::optional<Event> ConvertEvent(const SDL_WindowEvent& event);
[[nodiscard]] std::optional<Event> ConvertEvent(const SDL_KeyboardEvent& event);
[[nodiscard]] MouseMovedEvent      ConvertEvent(const SDL_MouseMotionEvent& event);
[[nodiscard]] MouseScrolledEvent   ConvertEvent(const SDL_MouseWheelEvent& event);
[[nodiscard]] MouseButtonEvent     ConvertEvent(const SDL_MouseButtonEvent& event);
[[nodiscard]] std::optional<Event> ConvertEvent(const SDL_Event& event);

} // namespace fuse::sdl3
