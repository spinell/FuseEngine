#pragma once
#include <FuseCore/utils/EnumFlags.h>

#include <cstdint>
#include <string>
#include <type_traits> // for underlying_type_t

namespace fuse {

/// @brief Scancode is the physical representation of a key on the keyboard, independent of language and keyboard mapping.
enum class ScanCode : std::uint8_t {
    Unknown,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,

    Return,
    Escape,
    Backspace,
    Tab,
    Space,
    Minus,
    Equals,
    LeftBracket,
    RightBracket,
    Backslash,
    Semicolon,
    Apostrophe,
    Grave,
    Comma,
    Period,
    Slash,
    Capslock,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,

    Printscreen,
    Scrolllock,
    Pause,
    Insert,
    Home,
    PageUp,
    Delete,
    End,
    PageDown,

    ArrowRight,
    ArrowLeft,
    ArrowDown,
    ArrowUp,

    // Keypad
    KeyPadNumlock,
    KeyPadDivide,
    KeyPadMultiply,
    KeyPadMinus,
    KeyPadPlus,
    KeyPadEnter,
    KeyPad0,
    KeyPad1,
    KeyPad2,
    KeyPad3,
    KeyPad4,
    KeyPad5,
    KeyPad6,
    KeyPad7,
    KeyPad8,
    KeyPad9,
    KeyPadPeriod,

    Application,
    VolumeUp,   // Key that allow to raise up the sound
    VolumeDown, // Key that allow to raise down the sound
    CtrlLeft,
    CtrlRight,
    ShiftLeft,
    ShiftRight,
    AltLeft,
    AltRight, // SDL generate Ctrl-left than Alt-right
    GuiLeft,
    GuiRight,
    AudioNext,
    AudioPrev,
    AudioStop,
    AudioPlay,
    Mute,
    MediaSelect, // Key that allow to open audio application
    Count
};

/// @brief
enum class KeyCode {};

/// @brief Key modifier
enum class KeyModFlag : std::uint16_t {
    None       = 0,
    LeftShift  = 1 << 0,  // left Shift key is down
    RightShift = 1 << 1,  // right Shift key is down
    LeftCtrl   = 1 << 2,  // the left Ctrl (Control) key is down.
    RightCtrl  = 1 << 3,  // the right Ctrl (Control) key is down
    LeftAlt    = 1 << 4,  // the left Alt key is down
    RightAlt   = 1 << 5,  // the right Alt key is down
    LeftGUI    = 1 << 6,  // the left GUI key (often the Windows key) is down
    RightGUI   = 1 << 7,  // the right GUI key (often the Windows key) is down
    NumLock    = 1 << 8,  // the Num Lock key (may be located on an extended keypad) is down.
    CapsLock   = 1 << 9,  // the Caps Lock key is down
    Scroll     = 1 << 10, // the Scroll Lock key is down.
};

using KeyModMask = EnumFlags<KeyModFlag>;

/// @brief Mouse button.
enum class MouseButton : std::uint8_t {
    Unknow = 0,
    Left   = 1,
    Right  = 2,
    Middle = 3,
    X4     = 4,
    X5     = 5,
    X6     = 6,
    X7     = 7,
    X8     = 8,
};

/// @brief Mouse Button mask
enum class MouseButtonFlag : std::uint8_t {
    None   = 0,
    Left   = 1 << 0,
    Right  = 1 << 1,
    Middle = 1 << 2,
    X4     = 1 << 3,
    X5     = 1 << 4,
    X6     = 1 << 5,
    X7     = 1 << 6,
    X8     = 1 << 7,
};

using MouseButtonMask = EnumFlags<MouseButtonFlag>;


/// @brief Return the name of a MouseButton
const char* toString(MouseButton button);
std::string toString(MouseButtonMask mask);
std::string toString(KeyModMask flag);

} // namespace fuse
