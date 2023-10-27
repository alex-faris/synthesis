#pragma once

#include <cstdint>

#include "Engine/Window/Window.hpp"

#include "Win32Types.hpp"

namespace Engine
{
  class Win32Window : public Window
  {
  public:
    static Win32Window* sInstance;

    Win32Window(u32 width, u32 height);

    bool tryCreate();
    void update() override;
    WindowHandle getHandle() const override;
    u32 getWidth() const override;
    u32 getHeight() const override;
    void destroy();

  private:
    u32 mWidth;
    u32 mHeight;
    const c16* m_kTitle;
    HINSTANCE m_Instance;
    HWND m_Handle;

    bool createWindowClass();
    bool createWindowHandle();

    static LRESULT CALLBACK winProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
  };
}  // namespace Engine
