#pragma once
#include "Timer.h"

#include <FuseCore/Event.h>

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

    [[nodiscard]] const GameTimer& getGameTimer() const { return mTimer; }

    void quit() { mIsRunning = false; }

protected:
    /// @brief
    /// @return
    virtual bool onInit() { return true; }

    /// @brief
    virtual void onShutdown() {}

private:
    /// @brief
    /// @return
    bool init();

    /// @brief
    /// @return
    bool shutdown();

    std::unique_ptr<Window> mMainWindow;
    bool                    mIsRunning = true;
    GameTimer               mTimer;
};

} // namespace fuse
