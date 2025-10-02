#include "Input.h"

#include <SDL3/SDL.h>

#include <map>

namespace {

/// @brief State of a button/key.
enum class KeyState : std::uint8_t {
    None,    ///<! No stage, the key is up.
    Pressed, ///<! Pressed this frame.
    Held,    ///<! Currently down.
    Released ///<! Released this frame.
};

std::map<fuse::ScanCode, KeyState>    sKeyStates;
std::map<fuse::MouseButton, KeyState> sMouseButtonStates;
std::pair<float, float>               sMousePosition;
std::pair<float, float>               sMouseDelta;
std::pair<float, float>               sMouseWheel;

} // namespace

namespace fuse {

// ==================================================================================
//                                 KeyBoard
// ==================================================================================

bool Input::IsKeyPressed(ScanCode key) noexcept {
    if (const auto it = sKeyStates.find(key); it != sKeyStates.end()) {
        return it->second == KeyState::Pressed;
    }
    return false;
}

bool Input::IsKeyDown(ScanCode key) noexcept {
    if (const auto it = sKeyStates.find(key); it != sKeyStates.end()) {
        // check if it pressed this frame or held down because
        // the held state happen on the next frame.
        return it->second == KeyState::Pressed || it->second == KeyState::Held;
    }
    return false;
}

bool Input::IsKeyReleased(ScanCode key) noexcept {
    if (const auto it = sKeyStates.find(key); it != sKeyStates.end()) {
        return it->second == KeyState::Released;
    }
    return false;
}

// ==================================================================================
//                                 Mouse
// ==================================================================================

bool Input::IsButtonPressed(MouseButton button) noexcept {
    if (const auto it = sMouseButtonStates.find(button); it != sMouseButtonStates.end()) {
        return it->second == KeyState::Pressed;
    }
    return false;
}

bool Input::IsButtonDown(MouseButton button) noexcept {
    if (const auto it = sMouseButtonStates.find(button); it != sMouseButtonStates.end()) {
        // check if it pressed this frame or held down because
        // the held state happen on the next frame.
        return it->second == KeyState::Pressed || it->second == KeyState::Held;
    }
    return false;
}

bool Input::IsButtonReleased(MouseButton button) noexcept {
    if (const auto it = sMouseButtonStates.find(button); it != sMouseButtonStates.end()) {
        return it->second == KeyState::Released;
    }
    return false;
}

std::pair<float, float> Input::GetMousePosition() noexcept { return sMousePosition; }

std::pair<float, float> Input::GetMousePositionDelta() noexcept { return sMouseDelta; }

std::pair<float, float> Input::GetMouseScrollDelta() noexcept { return sMouseWheel; }

// ==================================================================================
//                          Internal functions
// ==================================================================================

void Input::UpdateStates() noexcept {
    // Update the keyboard state
    for (auto& ks : sKeyStates) {
        if (ks.second == KeyState::Pressed) {
            ks.second = KeyState::Held;
        }
        if (ks.second == KeyState::Released) {
            ks.second = KeyState::None;
        }
    }

    // Update the mouse button state
    for (auto& mbs : sMouseButtonStates) {
        if (mbs.second == KeyState::Pressed) {
            mbs.second = KeyState::Held;
        }
        if (mbs.second == KeyState::Released) {
            mbs.second = KeyState::None;
        }
    }

    // reset mouse delta position and delta scroll
    sMouseDelta = {};
    sMouseWheel = {};
}

void Input::OnEvent(const Event& e) noexcept {
    //
    // Keyboard
    //
    if (const auto* keyPressedEvent = e.getIf<KeyPressedEvent>()) {
        if (!keyPressedEvent->isRepeated()) {
            // Mark the key as pressed
            // We can ignore the repeat state, the key will be marked has held down
            // on the next call to Update().
            sKeyStates[keyPressedEvent->getScanCode()] = KeyState::Pressed;
        }
    } else if (const auto* keyReleasedEvent = e.getIf<KeyReleasedEvent>()) {
        // Mark the key as released
        sKeyStates[keyReleasedEvent->getScanCode()] = KeyState::Released;
    }
    //
    // Mouse
    //
    else if (const auto* mouseButtonEvent = e.getIf<MouseButtonEvent>()) {
        if (mouseButtonEvent->isPressed()) {
            // Mark the button as pressed
            sMouseButtonStates[mouseButtonEvent->getButton()] = KeyState::Pressed;
        } else {
            // Mark the button as released
            sMouseButtonStates[mouseButtonEvent->getButton()] = KeyState::Released;
        }
    } else if (const auto* mouseMovedEvent = e.getIf<MouseMovedEvent>()) {
        sMousePosition = mouseMovedEvent->getMousePosition();
        sMouseDelta    = mouseMovedEvent->getMouseDelta();
    } else if (const auto* mouseScrolledEvent = e.getIf<MouseScrolledEvent>()) {
        sMouseWheel = mouseScrolledEvent->getDelta();
    }
}

} // namespace fuse
