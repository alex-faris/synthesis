#include "Timer.hpp"

Engine::Timer::Timer()
    : mStartTimePoint(std::chrono::high_resolution_clock::now()), mLastTimePoint(mStartTimePoint),
      mDeltaTime(0.0), mIsVSyncEnabled(true), mTargetFrameRate(60),
      mTargetFrameRateDuration(1.0 / mTargetFrameRate)
{
}

void Engine::Timer::tick()
{
  auto now = std::chrono::high_resolution_clock::now();
  mDeltaTime = std::chrono::duration<f64>(now - mLastTimePoint).count();
  mLastTimePoint = now;

  if (mIsVSyncEnabled)
  {
    while (getTimeSinceLastTick() < mTargetFrameRateDuration)
    {
      // This function intentionally left blank
      // "Wait for it, wait for it, wait for it, wait..."
    }
  }
}

f64 Engine::Timer::getDeltaTime() const
{
  return mDeltaTime;
}

void Engine::Timer::toggleVSync()
{
  mIsVSyncEnabled = !mIsVSyncEnabled;
}

void Engine::Timer::setTargetFrameRate(u8 rate)
{
  mTargetFrameRate = rate;
  mTargetFrameRateDuration = 1.0 / mTargetFrameRate;
}

f64 Engine::Timer::getTimeSinceLastTick() const
{
  return std::chrono::duration<f64>(std::chrono::high_resolution_clock::now() - mLastTimePoint)
  .count();
}
