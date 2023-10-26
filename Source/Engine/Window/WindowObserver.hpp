#pragma once

#include <cstdint>

namespace Engine
{
  class Window;

  class WindowObserver
  {
  public:
    virtual void OnResize(std::uint32_t new_width, std::uint32_t new_height);
    virtual void OnClose();

  private:
  };
}  // namespace Engine
