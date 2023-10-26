#pragma once

#include <cstdint>

#include "Engine/Window/Window.hpp"

#include "Win32Types.hpp"

namespace Engine
{
  class Win32Window : public Window
  {
  public:
    static Win32Window* s_Instance;

    Win32Window(u32 width, u32 height);

    bool TryCreate();
    void Update() override;
    WindowHandle GetNativeHandle() const override;
    u32 GetNativeWidth() const override;
    u32 GetNativeHeight() const override;
    void Destroy();

  private:
    u32 m_Width;
    u32 m_Height;
    const c16* m_kTitle;
    HINSTANCE m_Instance;
    HWND m_Handle;

    bool InitWindowClass();
    bool InitWindowHandle();

    static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM w_param, LPARAM l_param);
  };
}  // namespace Engine
