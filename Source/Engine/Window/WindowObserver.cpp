#include "WindowObserver.hpp"

void Engine::WindowObserver::onResize(u32 new_width, u32 new_height)
{
  // These arguments assigned on purpose
  new_width = new_width;
  new_height = new_height;
}

void Engine::WindowObserver::onClose()
{
  // This function left blank on purpose
}
