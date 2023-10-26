#include "Timer.hpp"

Engine::Timer::Timer()
    : m_StartTimePoint(std::chrono::high_resolution_clock::now()),
      m_LastTimePoint(m_StartTimePoint), m_DeltaTime(0.0), m_IsVSyncEnabled(true),
      m_TargetFrameRate(60), m_TargetFrameDuration(1.0 / m_TargetFrameRate)
{
}

void Engine::Timer::Tick()
{
  auto now = std::chrono::high_resolution_clock::now();
  m_DeltaTime = std::chrono::duration<f64>(now - m_LastTimePoint).count();
  m_LastTimePoint = now;

  if (m_IsVSyncEnabled)
  {
    while (GetTimeSinceLastTick() < m_TargetFrameDuration)
    {
      // This function intentionally left blank
      // "Wait for it, wait for it, wait for it, wait..."
    }
  }
}

f64 Engine::Timer::GetDeltaTime() const
{
  return m_DeltaTime;
}

void Engine::Timer::ToggleVSync()
{
  m_IsVSyncEnabled = !m_IsVSyncEnabled;
}

void Engine::Timer::SetTargetFrameRate(u8 rate)
{
  m_TargetFrameRate = rate;
  m_TargetFrameDuration = 1.0 / m_TargetFrameRate;
}

f64 Engine::Timer::GetTimeSinceLastTick() const
{
  return std::chrono::duration<f64>(std::chrono::high_resolution_clock::now() - m_LastTimePoint)
  .count();
}
