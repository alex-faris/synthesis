#include "Win32Window.hpp"

#include <iostream>

Engine::Win32Window::Win32Window(int width, int height)
    : m_Width(width), m_Height(height), m_kTitle(L"Synthesis"), m_Instance(nullptr),
      m_Handle(nullptr)
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
  WNDCLASSEXW window_class = {};
  window_class.cbSize = sizeof(window_class);
  window_class.style = CS_OWNDC;
  window_class.lpfnWndProc = DefWindowProc;
  window_class.hInstance = m_Instance;
  window_class.lpszClassName = m_kTitle;

  if (!RegisterClassExW(&window_class))
  {
    return false;
  }

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

Engine::WindowHandle Engine::Win32Window::GetNativeHandle() const
{
  return m_Handle;
}

void Engine::Win32Window::Destroy()
{
  if (m_Handle)
  {
    DestroyWindow(m_Handle);
  }
}
