#pragma once

#include <memory>

#include <EGL/egl.h>

#include "Engine/Window/Window.hpp"

namespace Engine
{
  class EGLManager
  {
  public:
    EGLManager(Window* window);

    bool tryCreate();
    EGLDisplay getDisplay() const;
    EGLSurface getSurface() const;
    std::uint32_t getSurfaceWidth() const;
    std::uint32_t getSurfaceHeight() const;
    void destroy();

  private:
    Window* mWindow;
    EGLDisplay mDisplay;
    EGLConfig mConfig;
    EGLContext mContext;
    EGLSurface mSurface;

    bool createDisplay();
    bool createConfig();
    bool createContext();
    bool createSurface();
    bool initRendering();
  };
}  // namespace Engine
