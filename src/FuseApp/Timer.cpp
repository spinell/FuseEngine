#include "Timer.h"

#include <SDL3/SDL.h>

namespace fuse {


GameTimer::GameTimer() noexcept {
    const auto countsPerSec = SDL_GetPerformanceFrequency();
    mSecondsPerCount        = 1.0 / static_cast<double>(countsPerSec);
}

// Returns the total time elapsed since Reset() was called, NOT counting any
// time when the clock is stopped.
float GameTimer::totalTime() const noexcept {
    // If we are stopped, do not count the time that has passed since we stopped.
    // Moreover, if we previously already had a pause, the distance
    // mStopTime - mBaseTime includes paused time, which we do not want to count.
    // To correct this, we can subtract the paused time from mStopTime:
    //
    //                     |<--paused time-->|
    // ----*---------------*-----------------*------------*------------*------> time
    //  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime
    if (mStopped) {
        return static_cast<float>(static_cast<double>(mStopTime - mPausedTime - mBaseTime) *
                                  mSecondsPerCount);
    }
    // The distance mCurrTime - mBaseTime includes paused time,
    // which we do not want to count.  To correct this, we can subtract
    // the paused time from mCurrTime:
    //
    //  (mCurrTime - mPausedTime) - mBaseTime
    //
    //                     |<--paused time-->|
    // ----*---------------*-----------------*------------*------> time
    //  mBaseTime       mStopTime        startTime     mCurrTime
    return static_cast<float>(static_cast<double>(mCurrTime - mPausedTime - mBaseTime) *
                                mSecondsPerCount);
}

float GameTimer::deltaTime() const noexcept { return static_cast<float>(mDeltaTime); }

void GameTimer::reset() noexcept {
    const auto currTime = SDL_GetPerformanceCounter();
    mBaseTime           = currTime;
    mPrevTime           = currTime;
    mStopTime           = 0;
    mStopped            = false;
}

void GameTimer::start() noexcept {

    // Accumulate the time elapsed between stop and start pairs.
    //
    //                     |<-------d------->|
    // ----*---------------*-----------------*------------> time
    //  mBaseTime       mStopTime        startTime

    if (mStopped) {
        const auto startTime = SDL_GetPerformanceCounter();
        mPausedTime += (startTime - mStopTime);

        mPrevTime = startTime;
        mStopTime = 0;
        mStopped  = false;
    }
}

void GameTimer::stop() noexcept {
    if (!mStopped) {
        const auto currTime = SDL_GetPerformanceCounter();
        mStopTime           = currTime;
        mStopped            = true;
    }
}

void GameTimer::tick() noexcept {
    if (mStopped) {
        mDeltaTime = 0.0;
        return;
    }

    const auto currTime = SDL_GetPerformanceCounter();
    mCurrTime           = currTime;

    // Time difference between this frame and the previous.
    mDeltaTime = static_cast<double>(mCurrTime - mPrevTime) * mSecondsPerCount;

    // Prepare for next frame.
    mPrevTime = mCurrTime;

    // Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the
    // processor goes into a power save mode or we get shuffled to another
    // processor, then mDeltaTime can be negative.
    if (mDeltaTime < 0.0) {
        mDeltaTime = 0.0;
    }
}

} // namespace fuse
