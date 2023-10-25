#pragma once

#include <cstdint>

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
    virtual std::uint32_t GetNativeWidth() const = 0;
    virtual std::uint32_t GetNativeHeight() const = 0;
  };
}  // namespace Engine
