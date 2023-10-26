#include "Win32Window.hpp"

#include <iostream>

namespace Engine
{
  Win32Window* Win32Window::s_Instance = nullptr;
}  // namespace Engine

Engine::Win32Window::Win32Window(int width, int height)
    : m_Width(width), m_Height(height), m_kTitle(nullptr), m_Instance(nullptr), m_Handle(nullptr)
{
}

bool Engine::Win32Window::TryCreate()
{
  if (!InitWindowClass())
  {
    std::cerr << "Failed to initialize Win32 window class!" << std::endl;
    return false;
  }

  if (!InitWindowHandle())
  {
    std::cerr << "Failed to initialize Win32 window handle!" << std::endl;
    return false;
  }

  ShowWindow(m_Handle, SW_SHOW);
  return true;
}

bool Engine::Win32Window::InitWindowClass()
{
  m_kTitle = L"Synthesis";

  WNDCLASSEXW window_class = {};
  window_class.cbSize = sizeof(window_class);
  window_class.style = CS_OWNDC;
  window_class.lpfnWndProc = WindowProc;
  window_class.hInstance = m_Instance;
  window_class.lpszClassName = m_kTitle;

  if (!RegisterClassExW(&window_class))
  {
    return false;
  }

  s_Instance = this;
  return true;
}

bool Engine::Win32Window::InitWindowHandle()
{
  m_Handle = CreateWindowW(m_kTitle, m_kTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           m_Width, m_Height, nullptr, nullptr, m_Instance, nullptr);

  if (!m_Handle)
  {
    return false;
  }

  return true;
}

void Engine::Win32Window::Update()
{
  MSG msg;
  while (PeekMessageW(&msg, m_Handle, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
}

LRESULT Engine::Win32Window::WindowProc(HWND handle, UINT message, WPARAM w_param, LPARAM l_param)
{
  if (s_Instance)
  {
    switch (message)
    {
      case WM_SIZE:
      {
        uint32_t new_width = LOWORD(l_param);
        uint32_t new_height = HIWORD(l_param);
        s_Instance->NotifyResize(new_width, new_height);
        break;
      }

      case WM_CLOSE:
      {
        s_Instance->NotifyClose();
        s_Instance->Destroy();
        return 0;
      }

      case WM_DESTROY:
      {
        PostQuitMessage(0);
        return 0;
      }
    }
  }

  return DefWindowProcW(handle, message, w_param, l_param);
}

Engine::WindowHandle Engine::Win32Window::GetNativeHandle() const
{
  return m_Handle;
}

std::uint32_t Engine::Win32Window::GetNativeWidth() const
{
  return m_Width;
}

std::uint32_t Engine::Win32Window::GetNativeHeight() const
{
  return m_Height;
}

void Engine::Win32Window::Destroy()
{
  if (m_Handle)
  {
    DestroyWindow(m_Handle);
  }
}
