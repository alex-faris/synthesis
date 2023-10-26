#pragma once

#include <chrono>

#include "Engine/Types.hpp"

namespace Engine
{
  class Timer
  {
  public:
    Timer();

    void Tick();
    f64 GetDeltaTime() const;
    void ToggleVSync();
    void SetTargetFrameRate(u8 rate);

  private:
    std::chrono::high_resolution_clock::time_point m_StartTimePoint;
    std::chrono::high_resolution_clock::time_point m_LastTimePoint;
    f64 m_DeltaTime;
    b8 m_IsVSyncEnabled;
    u8 m_TargetFrameRate;
    f64 m_TargetFrameDuration;

    f64 GetTimeSinceLastTick() const;
  };
}  // namespace Engine
