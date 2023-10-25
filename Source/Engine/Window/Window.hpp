#pragma once

#if defined(_WIN32)
  #include "Win32/Win32Types.hpp"
#endif

namespace Engine
{
  class Window
  {
  public:
    virtual ~Window() = default;

    virtual WindowHandle GetNativeHandle() const = 0;

  private:
  };
}  // namespace Engine
