#pragma once
#include "Event.h"
#include "Timer.h"

#include <glad/glad.h>

#include <memory>

namespace fuse {

class Window;

/// @brief Base class for fuse application.
class Application {
public:
    /// @brief
    Application();

    /// @brief
    virtual ~Application();

    Application(const Application&)             = delete;
    Application(const Application&&)            = delete;
    Application& operator=(const Application&)  = delete;
    Application& operator=(const Application&&) = delete;

    /// @brief
    void run();


    /// @brief
    /// @param deltaTime
    virtual void onUpdate(float /*deltaTime*/) {}

    /// @brief
    virtual void onEvent(const Event& event);

    /// @brief
    virtual void onImGui() {}

protected:
    /// @brief
    /// @return
    virtual bool onInit() { return true; }

    /// @brief
    virtual void onShutdown() {}

    GameTimer mTimer; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

private:
    /// @brief
    /// @return
    bool init();

    /// @brief
    /// @return
    bool shutdown();

    std::unique_ptr<Window> mMainWindow;
    std::unique_ptr<Window> mMainWindow2;
    bool                    mIsRunning = true;
};

} // namespace fuse
