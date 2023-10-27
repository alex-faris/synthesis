#include "Window.hpp"

void Engine::Window::createObserver(WindowObserver* observer)
{
  mObservers.push_back(observer);
}

void Engine::Window::destroyObserver(WindowObserver* observer)
{
  mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer),
                    mObservers.end());
}

void Engine::Window::notifyResize(u32 new_width, u32 new_height) const
{
  for (WindowObserver* observer : mObservers)
  {
    observer->onResize(new_width, new_height);
  }
}

void Engine::Window::notifyClose()
{
  for (WindowObserver* observer : mObservers)
  {
    observer->onClose();
  }
}
