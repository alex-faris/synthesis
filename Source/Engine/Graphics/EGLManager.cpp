#include "EGLManager.hpp"

#include <iostream>

Engine::EGLManager::EGLManager(Engine::Window& window)
    : m_Window(window), m_Display(EGL_NO_DISPLAY), m_Config(nullptr), m_Context(EGL_NO_CONTEXT),
      m_Surface(EGL_NO_SURFACE)
{
}

bool Engine::EGLManager::TryCreate()
{
  if (!CreateDisplay())
  {
    std::cerr << "Failed to create EGL display!" << std::endl;
    return false;
  }

  if (!CreateConfig())
  {
    std::cerr << "Failed to create EGL configuration!" << std::endl;
    return false;
  }

  if (!CreateContext())
  {
    std::cerr << "Failed to create EGL context!" << std::endl;
    return false;
  }

  if (!CreateSurface())
  {
    std::cerr << "Failed to create EGL surface!" << std::endl;
    return false;
  }

  if (!InitRendering())
  {
    std::cerr << "Failed to make EGL context current!" << std::endl;
    return false;
  }

  return true;
}

EGLDisplay Engine::EGLManager::GetDisplay() const
{
  return m_Display;
}

EGLSurface Engine::EGLManager::GetSurface() const
{
  return m_Surface;
}

std::uint32_t Engine::EGLManager::GetSurfaceWidth() const
{
  return m_Window.GetNativeWidth();
}

std::uint32_t Engine::EGLManager::GetSurfaceHeight() const
{
  return m_Window.GetNativeHeight();
}

bool Engine::EGLManager::CreateDisplay()
{
  m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (m_Display == EGL_NO_DISPLAY)
  {
    return false;
  }

  if (!eglInitialize(m_Display, nullptr, nullptr))
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::CreateConfig()
{
  EGLint num_configs;
  const EGLint kConfigAttributes[] = {EGL_RED_SIZE,   8, EGL_GREEN_SIZE,      8,
                                      EGL_BLUE_SIZE,  8, EGL_ALPHA_SIZE,      8,
                                      EGL_DEPTH_SIZE, 8, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                                      EGL_NONE};

  if (!eglChooseConfig(m_Display, kConfigAttributes, &m_Config, 1, &num_configs))
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::CreateContext()
{
  const EGLint kContextAttributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

  m_Context = eglCreateContext(m_Display, m_Config, EGL_NO_CONTEXT, kContextAttributes);
  if (m_Context == EGL_NO_CONTEXT)
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::CreateSurface()
{
  EGLSurface surface = EGL_NO_SURFACE;

#if defined(_WIN32)
  Engine::WindowHandle handle = m_Window.GetNativeHandle();
  surface = eglCreateWindowSurface(m_Display, m_Config, handle, nullptr);
#else
  return false;
#endif

  m_Surface = surface;
  if (m_Surface == EGL_NO_SURFACE)
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::InitRendering()
{
  return eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context);
}

void Engine::EGLManager::Destroy()
{
  if (m_Surface != EGL_NO_SURFACE)
  {
    eglDestroySurface(m_Display, m_Surface);
    m_Surface = EGL_NO_SURFACE;
  }

  if (m_Context != EGL_NO_CONTEXT)
  {
    eglDestroyContext(m_Display, m_Context);
    m_Context = EGL_NO_CONTEXT;
  }

  if (m_Display != EGL_NO_DISPLAY)
  {
    eglTerminate(m_Display);
    m_Display = EGL_NO_DISPLAY;
  }
}
