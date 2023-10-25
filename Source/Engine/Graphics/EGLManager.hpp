#pragma once

#include "Engine/Window/Window.hpp"

#include <EGL/egl.h>
#include <memory>

namespace Engine
{
  class EGLManager
  {
  public:
    EGLManager(Engine::Window& window);

    bool TryCreate();
    void Destroy();

  private:
    Engine::Window& m_Window;
    EGLDisplay m_Display;
    EGLConfig m_Config;
    EGLContext m_Context;
    EGLSurface m_Surface;

    bool InitDisplay();
    bool InitConfig();
    bool InitContext();
    bool InitSurface();
  };
}  // namespace Engine
