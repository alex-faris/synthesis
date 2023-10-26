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

    Win32Window(int width, int height);

    bool TryCreate();
    void Update() override;
    WindowHandle GetNativeHandle() const override;
    std::uint32_t GetNativeWidth() const override;
    std::uint32_t GetNativeHeight() const override;
    void Destroy();

  private:
    std::uint32_t m_Width;
    std::uint32_t m_Height;
    const wchar_t* m_kTitle;
    HINSTANCE m_Instance;
    HWND m_Handle;

    bool InitWindowClass();
    bool InitWindowHandle();

    static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM w_param, LPARAM l_param);
  };
}  // namespace Engine
