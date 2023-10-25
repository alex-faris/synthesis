#include "EGLManager.hpp"

#include <iostream>

Engine::EGLManager::EGLManager(Engine::Window& window)
    : m_Window(window), m_Display(EGL_NO_DISPLAY), m_Config(nullptr), m_Context(EGL_NO_CONTEXT),
      m_Surface(EGL_NO_SURFACE)
{
}

bool Engine::EGLManager::TryCreate()
{
  if (!InitDisplay())
  {
    std::cerr << "Failed to initialize EGL display!" << std::endl;
    return false;
  }

  if (!InitConfig())
  {
    std::cerr << "Failed to initialize EGL configuration!" << std::endl;
    return false;
  }

  if (!InitContext())
  {
    std::cerr << "Failed to initialize EGL context!" << std::endl;
    return false;
  }

  if (!InitSurface())
  {
    std::cerr << "Failed to initialize EGL surface!" << std::endl;
    return false;
  }

  return true;
}

bool Engine::EGLManager::InitDisplay()
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

bool Engine::EGLManager::InitConfig()
{
  EGLint num_configs;
  const EGLint kConfigAttributes[] = {EGL_RED_SIZE,   8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE,    8,
                                      EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_STENCIL_SIZE, 8,
                                      EGL_NONE};

  if (!eglChooseConfig(m_Display, kConfigAttributes, &m_Config, 1, &num_configs))
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::InitContext()
{
  const EGLint kContextAttributes[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

  m_Context = eglCreateContext(m_Display, nullptr, EGL_NO_CONTEXT, kContextAttributes);
  if (m_Context == EGL_NO_CONTEXT)
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::InitSurface()
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
