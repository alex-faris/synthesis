#pragma once

#include "Engine/Types.hpp"

namespace Engine
{
  class Window;

  class WindowObserver
  {
  public:
    virtual void onResize(u32 newWidth, u32 newHeight);
    virtual void onClose();

  private:
  };
}  // namespace Engine
