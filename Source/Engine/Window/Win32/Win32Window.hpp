#pragma once

#include <cstdint>

#include "Engine/Window/Window.hpp"

#include "Win32Types.hpp"

namespace Engine
{
  class Win32Window : public Window
  {
  public:
    Win32Window(int width, int height);

    bool TryCreate();
    void Destroy();

    WindowHandle GetNativeHandle() const override;

  private:
    std::uint32_t m_Width;
    std::uint32_t m_Height;
    const wchar_t* m_kTitle;
    HINSTANCE m_Instance;
    HWND m_Handle;

    bool InitWindowClass();
    bool InitWindowHandle();
  };
}  // namespace Engine
