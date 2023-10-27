#include "Win32Window.hpp"

#include <iostream>

namespace Engine
{
  Win32Window* Win32Window::sInstance = nullptr;
}  // namespace Engine

Engine::Win32Window::Win32Window(u32 width, u32 height)
    : mWidth(width), mHeight(height), m_kTitle(nullptr), m_Instance(nullptr), m_Handle(nullptr)
{
}

bool Engine::Win32Window::tryCreate()
{
  if (!createWindowClass())
  {
    std::cerr << "Failed to initialize Win32 window class!" << std::endl;
    return false;
  }

  if (!createWindowHandle())
  {
    std::cerr << "Failed to initialize Win32 window handle!" << std::endl;
    return false;
  }

  ShowWindow(m_Handle, SW_SHOW);
  return true;
}

bool Engine::Win32Window::createWindowClass()
{
  m_kTitle = L"Synthesis";

  WNDCLASSEXW window_class = {};
  window_class.cbSize = sizeof(window_class);
  window_class.style = CS_OWNDC;
  window_class.lpfnWndProc = winProc;
  window_class.hInstance = m_Instance;
  window_class.lpszClassName = m_kTitle;

  if (!RegisterClassExW(&window_class))
  {
    return false;
  }

  sInstance = this;
  return true;
}

bool Engine::Win32Window::createWindowHandle()
{
  m_Handle = CreateWindowW(m_kTitle, m_kTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           mWidth, mHeight, nullptr, nullptr, m_Instance, nullptr);

  if (!m_Handle)
  {
    return false;
  }

  return true;
}

void Engine::Win32Window::update()
{
  MSG msg;
  while (PeekMessageW(&msg, m_Handle, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
}

LRESULT Engine::Win32Window::winProc(HWND handle, UINT message, WPARAM w_param, LPARAM l_param)
{
  if (sInstance)
  {
    switch (message)
    {
      case WM_SIZE:
      {
        u32 new_width = LOWORD(l_param);
        u32 new_height = HIWORD(l_param);
        sInstance->notifyResize(new_width, new_height);
        break;
      }

      case WM_CLOSE:
      {
        sInstance->notifyClose();
        sInstance->destroy();
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

Engine::WindowHandle Engine::Win32Window::getHandle() const
{
  return m_Handle;
}

u32 Engine::Win32Window::getWidth() const
{
  return mWidth;
}

u32 Engine::Win32Window::getHeight() const
{
  return mHeight;
}

void Engine::Win32Window::destroy()
{
  if (m_Handle)
  {
    DestroyWindow(m_Handle);
  }
}
