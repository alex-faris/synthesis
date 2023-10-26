#pragma once

#include <string>

#include "Engine/Timer/Timer.hpp"
#include "Engine/Window/WindowObserver.hpp"
#include "Shader/Shader.hpp"

#include "EGLManager.hpp"

namespace Engine
{
  class Renderer : public WindowObserver
  {
  public:
    Renderer(EGLManager* egl);
    ~Renderer();

    bool TryCreate();
    void Draw();
    void Update();
    void Destroy();

    void OnResize(u32 new_width, u32 new_height) override;

  private:
    EGLManager* m_EGL;
    Shader m_Shader;
    GLuint m_VertexBuffer;
    Timer m_Timer;
    f32 m_Angle;

    void SetupTriangle();
  };
}  // namespace Engine
