#include "Window.hpp"

void Engine::Window::CreateObserver(WindowObserver* observer)
{
  m_Observers.push_back(observer);
}

void Engine::Window::DestroyObserver(WindowObserver* observer)
{
  m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer),
                    m_Observers.end());
}

void Engine::Window::NotifyResize(u32 new_width, u32 new_height) const
{
  for (WindowObserver* observer : m_Observers)
  {
    observer->OnResize(new_width, new_height);
  }
}

void Engine::Window::NotifyClose()
{
  for (WindowObserver* observer : m_Observers)
  {
    observer->OnClose();
  }
}
