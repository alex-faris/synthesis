#pragma once

#include <memory>

#include <EGL/egl.h>

#include "Engine/Window/Window.hpp"

namespace Engine
{
  class EGLManager
  {
  public:
    EGLManager(Engine::Window& window);

    bool TryCreate();
    EGLDisplay GetDisplay() const;
    EGLSurface GetSurface() const;
    std::uint32_t GetSurfaceWidth() const;
    std::uint32_t GetSurfaceHeight() const;
    void Destroy();

  private:
    Engine::Window& m_Window;
    EGLDisplay m_Display;
    EGLConfig m_Config;
    EGLContext m_Context;
    EGLSurface m_Surface;

    bool CreateDisplay();
    bool CreateConfig();
    bool CreateContext();
    bool CreateSurface();
    bool InitRendering();
  };
}  // namespace Engine
