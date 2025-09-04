#include "SDL3Helper.h"

#include <spdlog/spdlog.h>

#include <format>

namespace fuse::sdl3 {

[[nodiscard]] MouseButton ConvertMouseButton(int button) noexcept {
    switch (button) {
            // clang-format off
        case SDL_BUTTON_LEFT:   return MouseButton::Left;
        case SDL_BUTTON_RIGHT:  return MouseButton::Right;
        case SDL_BUTTON_MIDDLE: return MouseButton::Middle;
        case SDL_BUTTON_X1:     return MouseButton::X4;
        case SDL_BUTTON_X2:     return MouseButton::X5;
        default:                return MouseButton::Unknow;
            // clang-format on
    }
}

[[nodiscard]] ScanCode ConvertScanCode(SDL_Scancode scancode) noexcept {
    // clang-format off
    switch (scancode) {
        // NOLINTBEGIN(bugprone-branch-clone)
        case SDL_SCANCODE_A:                    return ScanCode::A;
        case SDL_SCANCODE_B:                    return ScanCode::B;
        case SDL_SCANCODE_C:                    return ScanCode::C;
        case SDL_SCANCODE_D:                    return ScanCode::D;
        case SDL_SCANCODE_E:                    return ScanCode::E;
        case SDL_SCANCODE_F:                    return ScanCode::F;
        case SDL_SCANCODE_G:                    return ScanCode::G;
        case SDL_SCANCODE_H:                    return ScanCode::H;
        case SDL_SCANCODE_I:                    return ScanCode::I;
        case SDL_SCANCODE_J:                    return ScanCode::J;
        case SDL_SCANCODE_K:                    return ScanCode::K;
        case SDL_SCANCODE_L:                    return ScanCode::L;
        case SDL_SCANCODE_M:                    return ScanCode::M;
        case SDL_SCANCODE_N:                    return ScanCode::N;
        case SDL_SCANCODE_O:                    return ScanCode::O;
        case SDL_SCANCODE_P:                    return ScanCode::P;
        case SDL_SCANCODE_Q:                    return ScanCode::Q;
        case SDL_SCANCODE_R:                    return ScanCode::R;
        case SDL_SCANCODE_S:                    return ScanCode::S;
        case SDL_SCANCODE_T:                    return ScanCode::T;
        case SDL_SCANCODE_U:                    return ScanCode::U;
        case SDL_SCANCODE_V:                    return ScanCode::V;
        case SDL_SCANCODE_W:                    return ScanCode::W;
        case SDL_SCANCODE_X:                    return ScanCode::X;
        case SDL_SCANCODE_Y:                    return ScanCode::Y;
        case SDL_SCANCODE_Z:                    return ScanCode::Z;
        case SDL_SCANCODE_1:                    return ScanCode::Key1;
        case SDL_SCANCODE_2:                    return ScanCode::Key2;
        case SDL_SCANCODE_3:                    return ScanCode::Key3;
        case SDL_SCANCODE_4:                    return ScanCode::Key4;
        case SDL_SCANCODE_5:                    return ScanCode::Key5;
        case SDL_SCANCODE_6:                    return ScanCode::Key6;
        case SDL_SCANCODE_7:                    return ScanCode::Key7;
        case SDL_SCANCODE_8:                    return ScanCode::Key8;
        case SDL_SCANCODE_9:                    return ScanCode::Key9;
        case SDL_SCANCODE_0:                    return ScanCode::Key0;
        case SDL_SCANCODE_RETURN:               return ScanCode::Return;
        case SDL_SCANCODE_ESCAPE:               return ScanCode::Escape;
        case SDL_SCANCODE_BACKSPACE:            return ScanCode::Backspace;
        case SDL_SCANCODE_TAB:                  return ScanCode::Tab;
        case SDL_SCANCODE_SPACE:                return ScanCode::Space;
        case SDL_SCANCODE_MINUS:                return ScanCode::Minus;
        case SDL_SCANCODE_EQUALS:               return ScanCode::Equals;
        case SDL_SCANCODE_LEFTBRACKET:          return ScanCode::LeftBracket;
        case SDL_SCANCODE_RIGHTBRACKET:         return ScanCode::RightBracket;
        case SDL_SCANCODE_BACKSLASH:            return ScanCode::Backslash;
        case SDL_SCANCODE_NONUSHASH:			return ScanCode::Unknown;
        case SDL_SCANCODE_SEMICOLON:            return ScanCode::Semicolon;
        case SDL_SCANCODE_APOSTROPHE:           return ScanCode::Apostrophe;
        case SDL_SCANCODE_GRAVE:                return ScanCode::Grave;
        case SDL_SCANCODE_COMMA:                return ScanCode::Comma;
        case SDL_SCANCODE_PERIOD:               return ScanCode::Period;
        case SDL_SCANCODE_SLASH:                return ScanCode::Slash;
        case SDL_SCANCODE_CAPSLOCK:             return ScanCode::Capslock;
        case SDL_SCANCODE_F1:                   return ScanCode::F1;
        case SDL_SCANCODE_F2:                   return ScanCode::F2;
        case SDL_SCANCODE_F3:                   return ScanCode::F3;
        case SDL_SCANCODE_F4:                   return ScanCode::F4;
        case SDL_SCANCODE_F5:                   return ScanCode::F5;
        case SDL_SCANCODE_F6:                   return ScanCode::F6;
        case SDL_SCANCODE_F7:                   return ScanCode::F7;
        case SDL_SCANCODE_F8:                   return ScanCode::F8;
        case SDL_SCANCODE_F9:                   return ScanCode::F9;
        case SDL_SCANCODE_F10:                  return ScanCode::F10;
        case SDL_SCANCODE_F11:                  return ScanCode::F11;
        case SDL_SCANCODE_F12:                  return ScanCode::F12;
        case SDL_SCANCODE_PRINTSCREEN:          return ScanCode::Printscreen;
        case SDL_SCANCODE_SCROLLLOCK:           return ScanCode::Scrolllock;
        case SDL_SCANCODE_PAUSE:                return ScanCode::Pause;
        case SDL_SCANCODE_INSERT:               return ScanCode::Insert;
        case SDL_SCANCODE_HOME:                 return ScanCode::Home;
        case SDL_SCANCODE_PAGEUP:               return ScanCode::PageUp;
        case SDL_SCANCODE_DELETE:               return ScanCode::Delete;
        case SDL_SCANCODE_END:                  return ScanCode::End;
        case SDL_SCANCODE_PAGEDOWN:             return ScanCode::PageDown;
        case SDL_SCANCODE_RIGHT:                return ScanCode::ArrowRight;
        case SDL_SCANCODE_LEFT:                 return ScanCode::ArrowLeft;
        case SDL_SCANCODE_DOWN:                 return ScanCode::ArrowDown;
        case SDL_SCANCODE_UP:                   return ScanCode::ArrowUp;
        case SDL_SCANCODE_NUMLOCKCLEAR:         return ScanCode::KeyPadNumlock;
        case SDL_SCANCODE_KP_DIVIDE:            return ScanCode::KeyPadDivide;
        case SDL_SCANCODE_KP_MULTIPLY:          return ScanCode::KeyPadMultiply;
        case SDL_SCANCODE_KP_MINUS:             return ScanCode::KeyPadMinus;
        case SDL_SCANCODE_KP_PLUS:              return ScanCode::KeyPadPlus;
        case SDL_SCANCODE_KP_ENTER:             return ScanCode::KeyPadEnter;
        case SDL_SCANCODE_KP_1:                 return ScanCode::KeyPad1;
        case SDL_SCANCODE_KP_2:                 return ScanCode::KeyPad2;
        case SDL_SCANCODE_KP_3:                 return ScanCode::KeyPad3;
        case SDL_SCANCODE_KP_4:                 return ScanCode::KeyPad4;
        case SDL_SCANCODE_KP_5:                 return ScanCode::KeyPad5;
        case SDL_SCANCODE_KP_6:                 return ScanCode::KeyPad6;
        case SDL_SCANCODE_KP_7:                 return ScanCode::KeyPad7;
        case SDL_SCANCODE_KP_8:                 return ScanCode::KeyPad8;
        case SDL_SCANCODE_KP_9:                 return ScanCode::KeyPad9;
        case SDL_SCANCODE_KP_0:                 return ScanCode::KeyPad0;
        case SDL_SCANCODE_KP_PERIOD:            return ScanCode::KeyPadPeriod;
        case SDL_SCANCODE_NONUSBACKSLASH:       return ScanCode::Unknown;
        case SDL_SCANCODE_APPLICATION:          return ScanCode::Application;
        case SDL_SCANCODE_POWER:                return ScanCode::Unknown;
        case SDL_SCANCODE_KP_EQUALS:            return ScanCode::Unknown;
        case SDL_SCANCODE_F13:                  return ScanCode::F13;
        case SDL_SCANCODE_F14:                  return ScanCode::F14;
        case SDL_SCANCODE_F15:                  return ScanCode::F15;
        case SDL_SCANCODE_F16:                  return ScanCode::F16;
        case SDL_SCANCODE_F17:                  return ScanCode::F17;
        case SDL_SCANCODE_F18:                  return ScanCode::F18;
        case SDL_SCANCODE_F19:                  return ScanCode::F19;
        case SDL_SCANCODE_F20:                  return ScanCode::F20;
        case SDL_SCANCODE_F21:                  return ScanCode::F21;
        case SDL_SCANCODE_F22:                  return ScanCode::F22;
        case SDL_SCANCODE_F23:                  return ScanCode::F23;
        case SDL_SCANCODE_F24:                  return ScanCode::F24;
        case SDL_SCANCODE_EXECUTE:              return ScanCode::Unknown;
        case SDL_SCANCODE_HELP:                 return ScanCode::Unknown;
        case SDL_SCANCODE_MENU:                 return ScanCode::Unknown;
        case SDL_SCANCODE_SELECT:               return ScanCode::Unknown;
        case SDL_SCANCODE_STOP:                 return ScanCode::Unknown;
        case SDL_SCANCODE_AGAIN:                return ScanCode::Unknown;
        case SDL_SCANCODE_UNDO:                 return ScanCode::Unknown;
        case SDL_SCANCODE_CUT:                  return ScanCode::Unknown;
        case SDL_SCANCODE_COPY:                 return ScanCode::Unknown;
        case SDL_SCANCODE_PASTE:                return ScanCode::Unknown;
        case SDL_SCANCODE_FIND:                 return ScanCode::Unknown;
        case SDL_SCANCODE_MUTE:                 return ScanCode::Mute;
        case SDL_SCANCODE_VOLUMEUP:             return ScanCode::VolumeUp;
        case SDL_SCANCODE_VOLUMEDOWN:           return ScanCode::VolumeDown;
        case SDL_SCANCODE_KP_COMMA:             return ScanCode::Unknown;
        case SDL_SCANCODE_KP_EQUALSAS400:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL1:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL2:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL3:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL4:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL5:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL6:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL7:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL8:       return ScanCode::Unknown;
        case SDL_SCANCODE_INTERNATIONAL9:       return ScanCode::Unknown;
        case SDL_SCANCODE_LANG1:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG2:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG3:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG4:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG5:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG6:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG7:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG8:                return ScanCode::Unknown;
        case SDL_SCANCODE_LANG9:                return ScanCode::Unknown;
        case SDL_SCANCODE_ALTERASE:             return ScanCode::Unknown;
        case SDL_SCANCODE_SYSREQ:               return ScanCode::Unknown;
        case SDL_SCANCODE_CANCEL:               return ScanCode::Unknown;
        case SDL_SCANCODE_CLEAR:                return ScanCode::Unknown;
        case SDL_SCANCODE_PRIOR:                return ScanCode::Unknown;
        case SDL_SCANCODE_RETURN2:              return ScanCode::Unknown;
        case SDL_SCANCODE_SEPARATOR:            return ScanCode::Unknown;
        case SDL_SCANCODE_OUT:                  return ScanCode::Unknown;
        case SDL_SCANCODE_OPER:                 return ScanCode::Unknown;
        case SDL_SCANCODE_CLEARAGAIN:           return ScanCode::Unknown;
        case SDL_SCANCODE_CRSEL:                return ScanCode::Unknown;
        case SDL_SCANCODE_EXSEL:                return ScanCode::Unknown;
        case SDL_SCANCODE_KP_00:                return ScanCode::Unknown;
        case SDL_SCANCODE_KP_000:               return ScanCode::Unknown;
        case SDL_SCANCODE_THOUSANDSSEPARATOR:   return ScanCode::Unknown;
        case SDL_SCANCODE_DECIMALSEPARATOR:     return ScanCode::Unknown;
        case SDL_SCANCODE_CURRENCYUNIT:         return ScanCode::Unknown;
        case SDL_SCANCODE_CURRENCYSUBUNIT:      return ScanCode::Unknown;
        case SDL_SCANCODE_KP_LEFTPAREN:         return ScanCode::Unknown;
        case SDL_SCANCODE_KP_RIGHTPAREN:        return ScanCode::Unknown;
        case SDL_SCANCODE_KP_LEFTBRACE:         return ScanCode::Unknown;
        case SDL_SCANCODE_KP_RIGHTBRACE:        return ScanCode::Unknown;
        case SDL_SCANCODE_KP_TAB:               return ScanCode::Unknown;
        case SDL_SCANCODE_KP_BACKSPACE:         return ScanCode::Unknown;
        case SDL_SCANCODE_KP_A:                 return ScanCode::Unknown;
        case SDL_SCANCODE_KP_B:                 return ScanCode::Unknown;
        case SDL_SCANCODE_KP_C:                 return ScanCode::Unknown;
        case SDL_SCANCODE_KP_D:                 return ScanCode::Unknown;
        case SDL_SCANCODE_KP_E:                 return ScanCode::Unknown;
        case SDL_SCANCODE_KP_F:                 return ScanCode::Unknown;
        case SDL_SCANCODE_KP_XOR:               return ScanCode::Unknown;
        case SDL_SCANCODE_KP_POWER:             return ScanCode::Unknown;
        case SDL_SCANCODE_KP_PERCENT:           return ScanCode::Unknown;
        case SDL_SCANCODE_KP_LESS:              return ScanCode::Unknown;
        case SDL_SCANCODE_KP_GREATER:           return ScanCode::Unknown;
        case SDL_SCANCODE_KP_AMPERSAND:         return ScanCode::Unknown;
        case SDL_SCANCODE_KP_DBLAMPERSAND:      return ScanCode::Unknown;
        case SDL_SCANCODE_KP_VERTICALBAR:       return ScanCode::Unknown;
        case SDL_SCANCODE_KP_DBLVERTICALBAR:    return ScanCode::Unknown;
        case SDL_SCANCODE_KP_COLON:             return ScanCode::Unknown;
        case SDL_SCANCODE_KP_HASH:              return ScanCode::Unknown;
        case SDL_SCANCODE_KP_SPACE:             return ScanCode::Unknown;
        case SDL_SCANCODE_KP_AT:                return ScanCode::Unknown;
        case SDL_SCANCODE_KP_EXCLAM:            return ScanCode::Unknown;
        case SDL_SCANCODE_KP_MEMSTORE:          return ScanCode::Unknown;
        case SDL_SCANCODE_KP_MEMRECALL:         return ScanCode::Unknown;
        case SDL_SCANCODE_KP_MEMCLEAR:          return ScanCode::Unknown;
        case SDL_SCANCODE_KP_MEMADD:            return ScanCode::Unknown;
        case SDL_SCANCODE_KP_MEMSUBTRACT:       return ScanCode::Unknown;
        case SDL_SCANCODE_KP_MEMMULTIPLY:       return ScanCode::Unknown;
        case SDL_SCANCODE_KP_MEMDIVIDE:         return ScanCode::Unknown;
        case SDL_SCANCODE_KP_PLUSMINUS:         return ScanCode::Unknown;
        case SDL_SCANCODE_KP_CLEAR:             return ScanCode::Unknown;
        case SDL_SCANCODE_KP_CLEARENTRY:        return ScanCode::Unknown;
        case SDL_SCANCODE_KP_BINARY:            return ScanCode::Unknown;
        case SDL_SCANCODE_KP_OCTAL:             return ScanCode::Unknown;
        case SDL_SCANCODE_KP_DECIMAL:           return ScanCode::Unknown;
        case SDL_SCANCODE_KP_HEXADECIMAL:       return ScanCode::Unknown;
        case SDL_SCANCODE_LCTRL:                return ScanCode::CtrlLeft;
        case SDL_SCANCODE_LSHIFT:               return ScanCode::ShiftLeft;
        case SDL_SCANCODE_LALT:                 return ScanCode::AltLeft;
        case SDL_SCANCODE_LGUI:                 return ScanCode::GuiLeft;
        case SDL_SCANCODE_RCTRL:                return ScanCode::CtrlRight;
        case SDL_SCANCODE_RSHIFT:               return ScanCode::ShiftRight;
        case SDL_SCANCODE_RALT:                 return ScanCode::AltRight;
        case SDL_SCANCODE_RGUI:                 return ScanCode::GuiRight;
        case SDL_SCANCODE_MODE:                 return ScanCode::Unknown;
        case SDL_SCANCODE_MEDIA_NEXT_TRACK:     return ScanCode::AudioNext;
        case SDL_SCANCODE_MEDIA_PREVIOUS_TRACK: return ScanCode::AudioPrev;
        case SDL_SCANCODE_MEDIA_STOP:           return ScanCode::AudioStop;
        case SDL_SCANCODE_MEDIA_PLAY:           return ScanCode::Unknown; // ???
        case SDL_SCANCODE_MEDIA_SELECT:         return ScanCode::MediaSelect;
        case SDL_SCANCODE_AC_SEARCH:            return ScanCode::Unknown;
        case SDL_SCANCODE_AC_HOME:              return ScanCode::Unknown;
        case SDL_SCANCODE_AC_BACK:              return ScanCode::Unknown;
        case SDL_SCANCODE_AC_FORWARD:           return ScanCode::Unknown;
        case SDL_SCANCODE_AC_STOP:              return ScanCode::Unknown;
        case SDL_SCANCODE_AC_REFRESH:           return ScanCode::Unknown;
        case SDL_SCANCODE_AC_BOOKMARKS:         return ScanCode::Unknown;
        case SDL_SCANCODE_MEDIA_EJECT:          return ScanCode::Unknown;
        case SDL_SCANCODE_MEDIA_PLAY_PAUSE:     return ScanCode::AudioPlay; // fixme
        case SDL_SCANCODE_SLEEP:                return ScanCode::Unknown;
        case SDL_SCANCODE_MEDIA_REWIND:         return ScanCode::Unknown;
        case SDL_SCANCODE_MEDIA_FAST_FORWARD:   return ScanCode::Unknown;
        case SDL_SCANCODE_UNKNOWN:              return ScanCode::Unknown;
        case SDL_SCANCODE_WAKE:                 return ScanCode::Unknown;
        case SDL_SCANCODE_CHANNEL_INCREMENT:    return ScanCode::Unknown;
        case SDL_SCANCODE_CHANNEL_DECREMENT:    return ScanCode::Unknown;
        case SDL_SCANCODE_MEDIA_PAUSE:          return ScanCode::Unknown;
        case SDL_SCANCODE_MEDIA_RECORD:         return ScanCode::Unknown;
        case SDL_SCANCODE_AC_NEW:               return ScanCode::Unknown;
        case SDL_SCANCODE_AC_OPEN:              return ScanCode::Unknown;
        case SDL_SCANCODE_AC_CLOSE:             return ScanCode::Unknown;
        case SDL_SCANCODE_AC_EXIT:              return ScanCode::Unknown;
        case SDL_SCANCODE_AC_SAVE:              return ScanCode::Unknown;
        case SDL_SCANCODE_AC_PRINT:             return ScanCode::Unknown;
        case SDL_SCANCODE_AC_PROPERTIES:        return ScanCode::Unknown;
        case SDL_SCANCODE_SOFTLEFT:             return ScanCode::Unknown;
        case SDL_SCANCODE_SOFTRIGHT:            return ScanCode::Unknown;
        case SDL_SCANCODE_CALL:                 return ScanCode::Unknown;
        case SDL_SCANCODE_ENDCALL:              return ScanCode::Unknown;
        case SDL_SCANCODE_RESERVED:             return ScanCode::Unknown;
        case SDL_SCANCODE_COUNT:                return ScanCode::Unknown; // not a key
        default:                                return ScanCode::Unknown;
        // NOLINTEND(bugprone-branch-clone)
    }
    // clang-format on
}

[[nodiscard]] MouseButtonMask ConvertMouseButtonMask(SDL_MouseButtonFlags buttonMask) noexcept {
    MouseButtonMask mask{};
    if ((buttonMask & SDL_BUTTON_LMASK) == SDL_BUTTON_LMASK) {
        mask.set(MouseButtonFlag::Left);
    }
    if ((buttonMask & SDL_BUTTON_MMASK) == SDL_BUTTON_MMASK) {
        mask.set(MouseButtonFlag::Middle);
    }
    if ((buttonMask & SDL_BUTTON_RMASK) == SDL_BUTTON_RMASK) {
        mask.set(MouseButtonFlag::Right);
    }
    if ((buttonMask & SDL_BUTTON_X1MASK) == SDL_BUTTON_X1MASK) {
        mask.set(MouseButtonFlag::X4);
    }
    if ((buttonMask & SDL_BUTTON_X2MASK) == SDL_BUTTON_X2MASK) {
        mask.set(MouseButtonFlag::X5);
    }
    return mask;
}

[[nodiscard]] KeyModMask ConvertKeyModifierMask(SDL_Keymod keymod) noexcept {
    KeyModMask mod{};
    if ((keymod & SDL_KMOD_LSHIFT) == SDL_KMOD_LSHIFT) {
        mod.set(KeyModFlag::LeftShift);
    }
    if ((keymod & SDL_KMOD_RSHIFT) == SDL_KMOD_RSHIFT) {
        mod.set(KeyModFlag::RightShift);
    }
    if ((keymod & SDL_KMOD_LCTRL) == SDL_KMOD_LCTRL) {
        mod.set(KeyModFlag::LeftCtrl);
    }
    if ((keymod & SDL_KMOD_RCTRL) == SDL_KMOD_RCTRL) {
        mod.set(KeyModFlag::RightCtrl);
    }
    if ((keymod & SDL_KMOD_LALT) == SDL_KMOD_LALT) {
        mod.set(KeyModFlag::LeftAlt);
    }
    if ((keymod & SDL_KMOD_RALT) == SDL_KMOD_RALT) {
        mod.set(KeyModFlag::RightAlt);
    }
    if ((keymod & SDL_KMOD_LGUI) == SDL_KMOD_LGUI) {
        mod.set(KeyModFlag::LeftGUI);
    }
    if ((keymod & SDL_KMOD_RGUI) == SDL_KMOD_RGUI) {
        mod.set(KeyModFlag::RightGUI);
    }
    if ((keymod & SDL_KMOD_NUM) == SDL_KMOD_NUM) {
        mod.set(KeyModFlag::NumLock);
    }
    if ((keymod & SDL_KMOD_CAPS) == SDL_KMOD_CAPS) {
        mod.set(KeyModFlag::CapsLock);
    }
    if ((keymod & SDL_KMOD_MODE) == SDL_KMOD_MODE) {
        // mod |= (KeyModFlag)SDL_KMOD_MODE;
    }
    if ((keymod & SDL_KMOD_SCROLL) == SDL_KMOD_SCROLL) {
        mod.set(KeyModFlag::Scroll);
    }
    return mod;
}

[[nodiscard]] std::optional<Event> ConvertEvent(const SDL_KeyboardEvent& event) {
    const ScanCode   scanCode = ConvertScanCode(event.scancode);
    const KeyModMask mod      = ConvertKeyModifierMask(event.mod);
    if (event.down) {
        return KeyPressedEvent(scanCode, KeyCode{}, event.repeat, mod);
    }

    return KeyReleasedEvent(scanCode, KeyCode{}, mod);
}

[[nodiscard]] MouseMovedEvent ConvertEvent(const SDL_MouseMotionEvent& event) {
    const auto buttonMask = ConvertMouseButtonMask(event.state);
    return {event.x, event.y, event.xrel, event.yrel, buttonMask};
}

[[nodiscard]] MouseScrolledEvent ConvertEvent(const SDL_MouseWheelEvent& event) {
    const SDL_MouseWheelDirection direction = event.direction;
    const float                   deltaX = direction == SDL_MOUSEWHEEL_FLIPPED ? -event.x : event.x;
    const float                   deltaY = direction == SDL_MOUSEWHEEL_FLIPPED ? -event.y : event.y;
    return {deltaX, deltaY, event.mouse_x, event.mouse_y};
}

[[nodiscard]] MouseButtonEvent ConvertEvent(const SDL_MouseButtonEvent& event) {
    const MouseButton button = ConvertMouseButton(event.button);
    return {button, event.down, event.clicks, event.x, event.y};
}

[[nodiscard]] std::optional<Event> ConvertEvent(const SDL_WindowEvent& event) {
    // NOLINTBEGIN(bugprone-branch-clone)
    if (event.type == SDL_EVENT_WINDOW_SHOWN) {
        //
        // Do we need this ?
        //
        //spdlog::info("[Window {}] SDL_EVENT_WINDOW_SHOWN", event.windowID);
    } else if (event.type == SDL_EVENT_WINDOW_HIDDEN) {
        //
        // Do we need this ?
        //
    } else if (event.type == SDL_EVENT_WINDOW_EXPOSED) {
        //
        // Do we need this ?
        //
    } else if (event.type == SDL_EVENT_WINDOW_MOVED) {
        return WindowMovedEvent(event.data1, event.data2);
    } else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
        return WindowResizedEvent(event.data1, event.data2);
    } else if (event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
        //
        // WTF is this event ?
        //
    } else if (event.type == SDL_EVENT_WINDOW_METAL_VIEW_RESIZED) {
        //
        // WTF is this event ?
        //
    } else if (event.type == SDL_EVENT_WINDOW_MINIMIZED) {
        return WindowMinimizedEvent();
    } else if (event.type == SDL_EVENT_WINDOW_MAXIMIZED) {
        return WindowMaximizedEvent();
    } else if (event.type == SDL_EVENT_WINDOW_RESTORED) {
        return WindowRestoredEvent();
    } else if (event.type == SDL_EVENT_WINDOW_MOUSE_ENTER) {
        return WindowMouseEnterEvent();
    } else if (event.type == SDL_EVENT_WINDOW_MOUSE_LEAVE) {
        return WindowMouseLeaveEvent();
    } else if (event.type == SDL_EVENT_WINDOW_FOCUS_GAINED) {
        return WindowFocusGainEvent();
    } else if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST) {
        return WindowFocusLostEvent();
    } else if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        return WindowCloseEvent();
    } else if (event.type == SDL_EVENT_WINDOW_HIT_TEST) {
        //
        // Do we need this ?
        //
        // ENGINE_CORE_DEBUG("[Window {}] SDL_EVENT_WINDOW_HIT_TEST", windowEvent.windowID);
    } else if (event.type == SDL_EVENT_WINDOW_ICCPROF_CHANGED) {
        //
        // Do we need this ?
        //
        // ENGINE_CORE_DEBUG("[Window {}] SDL_EVENT_WINDOW_ICCPROF_CHANGED", windowEvent.windowID);
    } else if (event.type == SDL_EVENT_WINDOW_DISPLAY_CHANGED) {
        return WindowDisplaydChangedEvent(/*event.data1*/);
    } else if (event.type == SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED) {
        //
        // Do we need this ?
        //
        // ENGINE_CORE_DEBUG("[Window {}] SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED {} {}",
        // windowEvent.windowID, windowEvent.data1, windowEvent.data2);
    } else if (event.type == SDL_EVENT_WINDOW_SAFE_AREA_CHANGED) {
        //
        // What is this event ?????
        //
    } else if (event.type == SDL_EVENT_WINDOW_OCCLUDED) {
        //
        // Look to do nothing ...
        //
    } else if (event.type == SDL_EVENT_WINDOW_ENTER_FULLSCREEN) {
        return WindowFullScreenEnterEvent();
    } else if (event.type == SDL_EVENT_WINDOW_LEAVE_FULLSCREEN) {
        return WindowFullScreenLeaveEvent();
    } else if (event.type == SDL_EVENT_WINDOW_DESTROYED) {
        // The window with the associated ID is being or has been destroyed.
        // If this message is being handled in an event watcher, the window handle
        // is still valid and can still be used to retrieve any properties
        // associated with the window. Otherwise, the handle has already been destroyed and all resources
        // associated with it are invalid
    } else if (event.type == SDL_EVENT_WINDOW_HDR_STATE_CHANGED) {
        //
        // Window HDR properties have changed
        //
    }
    // NOLINTEND(bugprone-branch-clone)
    return {};
}

[[nodiscard]] std::optional<Event> ConvertEvent(const SDL_Event& event) {
    // NOLINTBEGIN(bugprone-branch-clone)

    // process windows event
    if (event.type >= SDL_EVENT_WINDOW_FIRST && event.type <= SDL_EVENT_WINDOW_LAST) {
        return ConvertEvent(event.window);
    }
    ///
    /// Keyboard Events
    ///
    else if (event.type == SDL_EVENT_KEYBOARD_ADDED) {
        //spdlog::info("[KeyBoard added] ID : {}", event.which);
    } else if (event.type == SDL_EVENT_KEYBOARD_REMOVED) {
        //spdlog::info("[KeyBoard removed] ID : {}", event.which);
    } else if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
        const SDL_KeyboardEvent& keyEvent = event.key;
        return ConvertEvent(keyEvent);
    }
    ///
    /// Text Input Event
    ///
    else if (event.type == SDL_EVENT_TEXT_INPUT) {
        const SDL_TextInputEvent& textEvent = event.text;
        return TextInputEvent(textEvent.text);
    } else if (event.type == SDL_EVENT_TEXT_EDITING) {
        ///
        /// Keyboard text editing (composition)
        //
    } else if (event.type == SDL_EVENT_KEYMAP_CHANGED) {
        ///
        /// The keymap has changed
        ///
    } else if (event.type == SDL_EVENT_TEXT_EDITING_CANDIDATES) {
        ///
        /// Keyboard text editing candidates
        ///
    }
    ///
    /// Mouse Event
    ///
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        return ConvertEvent(event.button);
    } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        return ConvertEvent(event.motion);
    } else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
        return ConvertEvent(event.wheel);
    }
    ///
    /// Joystick Event
    ///
    else if (event.type == SDL_EVENT_JOYSTICK_ADDED) {
        const SDL_JoyDeviceEvent& deviceEvent = event.jdevice;
        spdlog::info("[JoyStick added] ID : {}", deviceEvent.which);
    } else if (event.type == SDL_EVENT_JOYSTICK_REMOVED) {
        const SDL_JoyDeviceEvent& deviceEvent = event.jdevice;
        spdlog::info("[JoyStick removed] ID : {}", deviceEvent.which);
    } else if (event.type == SDL_EVENT_JOYSTICK_BATTERY_UPDATED) {

    } else if (event.type == SDL_EVENT_JOYSTICK_UPDATE_COMPLETE) {
        // https://github.com/libsdl-org/SDL/commit/4c9fb3e16902607d978a2c2f9ade777ad232b628
        // This allows the application to tell when a joystick polling cycle is complete and can process state changes as a single atomic update.
        // It is disabled by default, at least for now.
        // spdlog::info("[JoyStick update] ID : {}", event.which);
    } else if (event.type == SDL_EVENT_JOYSTICK_AXIS_MOTION) {
        //const SDL_JoyAxisEvent& axisEvent = event.jaxis;
        //spdlog::info("[JoyStick axis motion] id {}, axis {}, value {}",
        //             axisEvent.which,
        //             axisEvent.axis,
        //             axisEvent.value);
    } else if (event.type == SDL_EVENT_JOYSTICK_BALL_MOTION) {
        const SDL_JoyBallEvent& ballEvent = event.jball;
        spdlog::info("[JoyStick ball motion] id {}, ball {}, xrel {}, yrel {}",
                     ballEvent.which,
                     ballEvent.ball,
                     ballEvent.xrel,
                     ballEvent.yrel);
    } else if (event.type == SDL_EVENT_JOYSTICK_HAT_MOTION) {
        const SDL_JoyHatEvent& hatEvent = event.jhat;
        spdlog::info("[JoyStick hat motion] id {}, hat {}, value {}",
                     hatEvent.which,
                     hatEvent.hat,
                     hatEvent.value);
    } else if (event.type == SDL_EVENT_JOYSTICK_BUTTON_DOWN) {
        //const SDL_JoyButtonEvent& buttonEvent = event.jbutton;
        //spdlog::info("[JButtonDown] id {}, button {}", buttonEvent.which, buttonEvent.button);
    } else if (event.type == SDL_EVENT_JOYSTICK_BUTTON_UP) {
        //const SDL_JoyButtonEvent& buttonEvent = event.jbutton;
        //spdlog::info("[JButtonUp] id {}, button {}", buttonEvent.which, buttonEvent.button);
    }
    ///
    /// Gamepad Event
    ///
    else if (event.type == SDL_EVENT_GAMEPAD_ADDED) {
        const SDL_GamepadDeviceEvent& gdevice = event.gdevice;
        spdlog::info("[GamePad added] ID : {}", gdevice.which);
    } else if (event.type == SDL_EVENT_GAMEPAD_REMOVED) {
        const SDL_GamepadDeviceEvent& gdevice = event.gdevice;
        spdlog::info("[GamePad removed] ID : {}", gdevice.which);
    } else if (event.type == SDL_EVENT_GAMEPAD_REMAPPED) {
        const SDL_GamepadDeviceEvent& gdevice = event.gdevice;
        spdlog::info("[GamePad remapped] ID : {}", gdevice.which);
    } else if (event.type == SDL_EVENT_GAMEPAD_UPDATE_COMPLETE) {
        // https://github.com/libsdl-org/SDL/commit/4c9fb3e16902607d978a2c2f9ade777ad232b628
        // This allows the application to tell when a joystick polling cycle is complete and can process state changes as a single atomic update.
        // It is disabled by default, at least for now.
        // spdlog::info("[GamePad update] ID : {}", event.which);
    } else if (event.type == SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED) {
        ///
        ///
        ///
        const SDL_GamepadButtonEvent& gbe = event.gbutton;
        spdlog::info("[GamePad steam update] ID : {}", gbe.which);
    } else if (event.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
        const SDL_GamepadAxisEvent& axisEvent = event.gaxis;
        const auto                  axis      = static_cast<SDL_GamepadAxis>(axisEvent.axis);
        spdlog::info("[gamepad axis motion] id {}, axis {}, value {}",
                     axisEvent.which,
                     SDL_GetGamepadStringForAxis(axis),
                     axisEvent.value);
    } else if (event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
        const SDL_GamepadButtonEvent& gbe    = event.gbutton;
        const auto                    button = static_cast<SDL_GamepadButton>(gbe.button);
        spdlog::info("[gamepad button pressed] id {}, button {}",
                     gbe.which,
                     SDL_GetGamepadStringForButton(button));
    } else if (event.type == SDL_EVENT_GAMEPAD_BUTTON_UP) {
        const SDL_GamepadButtonEvent& gbe    = event.gbutton;
        const auto                    button = static_cast<SDL_GamepadButton>(gbe.button);
        spdlog::info("[gamepad button release] id {}, button {}",
                     gbe.which,
                     SDL_GetGamepadStringForButton(button));
    } else if (event.type == SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN) {
        ///
        ///
        ///
    } else if (event.type == SDL_EVENT_GAMEPAD_TOUCHPAD_UP) {
        ///
        ///
        ///
    } else if (event.type == SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION) {
        ///
        ///
        ///
    } else if (event.type == SDL_EVENT_GAMEPAD_SENSOR_UPDATE) {
        ///
        ///
        ///
    }

    // NOLINTEND(bugprone-branch-clone)

    return {};
}

} // namespace fuse::sdl3
