#include "EGLManager.hpp"

#include <iostream>

Engine::EGLManager::EGLManager(Window* window)
    : mWindow(window), mDisplay(EGL_NO_DISPLAY), mConfig(nullptr), mContext(EGL_NO_CONTEXT),
      mSurface(EGL_NO_SURFACE)
{
}

bool Engine::EGLManager::tryCreate()
{
  if (!createDisplay())
  {
    std::cerr << "Failed to create EGL display!" << std::endl;
    return false;
  }

  if (!createConfig())
  {
    std::cerr << "Failed to create EGL configuration!" << std::endl;
    return false;
  }

  if (!createContext())
  {
    std::cerr << "Failed to create EGL context!" << std::endl;
    return false;
  }

  if (!createSurface())
  {
    std::cerr << "Failed to create EGL surface!" << std::endl;
    return false;
  }

  if (!initRendering())
  {
    std::cerr << "Failed to make EGL context current!" << std::endl;
    return false;
  }

  return true;
}

EGLDisplay Engine::EGLManager::getDisplay() const
{
  return mDisplay;
}

EGLSurface Engine::EGLManager::getSurface() const
{
  return mSurface;
}

std::uint32_t Engine::EGLManager::getSurfaceWidth() const
{
  return mWindow->getWidth();
}

std::uint32_t Engine::EGLManager::getSurfaceHeight() const
{
  return mWindow->getHeight();
}

bool Engine::EGLManager::createDisplay()
{
  mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (mDisplay == EGL_NO_DISPLAY)
  {
    return false;
  }

  if (!eglInitialize(mDisplay, nullptr, nullptr))
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::createConfig()
{
  EGLint num_configs;
  const EGLint kConfigAttributes[] = {EGL_RED_SIZE,   8, EGL_GREEN_SIZE,      8,
                                      EGL_BLUE_SIZE,  8, EGL_ALPHA_SIZE,      8,
                                      EGL_DEPTH_SIZE, 8, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                                      EGL_NONE};

  if (!eglChooseConfig(mDisplay, kConfigAttributes, &mConfig, 1, &num_configs))
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::createContext()
{
  const EGLint kContextAttributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

  mContext = eglCreateContext(mDisplay, mConfig, EGL_NO_CONTEXT, kContextAttributes);
  if (mContext == EGL_NO_CONTEXT)
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::createSurface()
{
  EGLSurface surface = EGL_NO_SURFACE;

#if defined(_WIN32)
  Engine::WindowHandle handle = mWindow->getHandle();
  surface = eglCreateWindowSurface(mDisplay, mConfig, handle, nullptr);
#else
  return false;
#endif

  mSurface = surface;
  if (mSurface == EGL_NO_SURFACE)
  {
    return false;
  }

  return true;
}

bool Engine::EGLManager::initRendering()
{
  return eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);
}

void Engine::EGLManager::destroy()
{
  if (mSurface != EGL_NO_SURFACE)
  {
    eglDestroySurface(mDisplay, mSurface);
    mSurface = EGL_NO_SURFACE;
  }

  if (mContext != EGL_NO_CONTEXT)
  {
    eglDestroyContext(mDisplay, mContext);
    mContext = EGL_NO_CONTEXT;
  }

  if (mDisplay != EGL_NO_DISPLAY)
  {
    eglTerminate(mDisplay);
    mDisplay = EGL_NO_DISPLAY;
  }
}
