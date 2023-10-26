#pragma once

#include "Engine/Types.hpp"

namespace Engine
{
  class Window;

  class WindowObserver
  {
  public:
    virtual void OnResize(u32 new_width, u32 new_height);
    virtual void OnClose();

  private:
  };
}  // namespace Engine
