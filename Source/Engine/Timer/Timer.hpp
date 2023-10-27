#pragma once

#include <chrono>

#include "Engine/Types.hpp"

namespace Engine
{
  class Timer
  {
  public:
    Timer();

    void tick();
    f64 getDeltaTime() const;
    void toggleVSync();
    void setTargetFrameRate(u8 rate);

  private:
    std::chrono::high_resolution_clock::time_point mStartTimePoint;
    std::chrono::high_resolution_clock::time_point mLastTimePoint;
    f64 mDeltaTime;
    b8 mIsVSyncEnabled;
    u8 mTargetFrameRate;
    f64 mTargetFrameRateDuration;

    f64 getTimeSinceLastTick() const;
  };
}  // namespace Engine
