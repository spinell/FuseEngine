#include "Event.h"

#include <format>

namespace fuse {

std::string MouseButtonEvent::toString() const {
    if (mIsPressed) {
        return std::format("ButtonPressed: {} ({},{}) click={}",
                           fuse::toString(mButton),
                           mMouseX,
                           mMouseY,
                           mClick);
    }
    return std::format("ButtonReleased: {} ({},{})", fuse::toString(mButton), mMouseX, mMouseY);
}

std::string MouseMovedEvent::toString() const {
    std::string str =
      std::format("MouseMoved: position [{},{}] delta [{},{}]", mPosX, mPosY, mDeltaX, mDeltaY);

    if (mButtonState.isAnySet()) {
        return std::format("{} [{}]", str, fuse::toString(mButtonState));
    }
    return str;
}

std::string MouseScrolledEvent::toString() const {
    return std::format("MouseScrolled: scroll [{},{}] position [{},{}]",
                       mDeltaX,
                       mDeltaY,
                       mMouseX,
                       mMouseY);
}

std::string WindowResizedEvent::toString() const {
    return std::format("WindowResized: {}x{}", mWidth, mHeight);
}

std::string WindowMovedEvent::toString() const {
    return std::format("WindowMoved: {},{}", mPosX, mPosY);
}

std::string KeyPressedEvent::toString() const {
    const std::string modFormat = mModifier.isAnySet() ? fuse::toString(mModifier) : "";

    return std::format("KeyPressed: key={} scanCode={} repeated={} [{}]",
                       static_cast<unsigned>(mKeyCode),
                       static_cast<unsigned>(mScanCode),
                       mIsRepeated,
                       modFormat);
}

std::string KeyReleasedEvent::toString() const {
    const std::string modFormat = mModifier.isAnySet() ? fuse::toString(mModifier) : "";
    return std::format("KeyReleased: key={} scanCode={} [{}]",
                       static_cast<unsigned>(mKeyCode),
                       static_cast<unsigned>(mScanCode),
                       modFormat);
}

std::string TextInputEvent::toString() const { return std::format("TextInputEvent: {}", mText); }

} // namespace fuse
