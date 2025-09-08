#include "Keyboard.h"

namespace fuse {

const char* toString(MouseButton button) {
    switch (button) {
            // clang-format off
        case MouseButton::Left:   return "Left";
        case MouseButton::Right:  return "Right";
        case MouseButton::Middle: return "Middle";
        case MouseButton::X4:     return "X4";
        case MouseButton::X5:     return "X5";
        case MouseButton::X6:     return "X6";
        case MouseButton::X7:     return "X7";
        case MouseButton::X8:     return "X8";
        case MouseButton::Unknow:
        default:                  return "Unknow";
            // clang-format on
    }
}

std::string toString(MouseButtonMask mask) {
    std::string str;
    auto        appendStr = [&str](std::string_view s) {
        if (!str.empty()) {
            str.append(" | ");
        }
        str.append(s);
    };

    if (mask.isSet(MouseButtonFlag::Left)) {
        appendStr("Left");
    }
    if (mask.isSet(MouseButtonFlag::Right)) {
        appendStr("Right");
    }
    if (mask.isSet(MouseButtonFlag::Middle)) {
        appendStr("Middle");
    }
    if (mask.isSet(MouseButtonFlag::X4)) {
        appendStr("X4");
    }
    if (mask.isSet(MouseButtonFlag::X5)) {
        appendStr("X5");
    }
    if (mask.isSet(MouseButtonFlag::X6)) {
        appendStr("X6");
    }
    if (mask.isSet(MouseButtonFlag::X7)) {
        appendStr("X7");
    }
    if (mask.isSet(MouseButtonFlag::X8)) {
        appendStr("X8");
    }
    return str;
}

std::string toString(KeyModMask flags) {
    std::string str;
    auto        appendStr = [&str](std::string_view s) {
        if (!str.empty()) {
            str.append(" | ");
        }
        str.append(s);
    };

    if (flags.isSet(KeyModFlag::LeftShift)) {
        appendStr("LeftShift");
    }
    if (flags.isSet(KeyModFlag::RightShift)) {
        appendStr("RightShift");
    }
    if (flags.isSet(KeyModFlag::LeftCtrl)) {
        appendStr("LeftCtrl");
    }
    if (flags.isSet(KeyModFlag::RightCtrl)) {
        appendStr("RightCtrl");
    }
    if (flags.isSet(KeyModFlag::LeftAlt)) {
        appendStr("LeftAlt");
    }
    if (flags.isSet(KeyModFlag::RightAlt)) {
        appendStr("RightAlt");
    }
    if (flags.isSet(KeyModFlag::LeftGUI)) {
        appendStr("LeftGUI");
    }
    if (flags.isSet(KeyModFlag::RightGUI)) {
        appendStr("RightGUI");
    }
    if (flags.isSet(KeyModFlag::NumLock)) {
        appendStr("NumLock");
    }
    if (flags.isSet(KeyModFlag::CapsLock)) {
        appendStr("CapsLock");
    }
    if (flags.isSet(KeyModFlag::Scroll)) {
        appendStr("Scroll");
    }
    return str;
}

} // namespace fuse
