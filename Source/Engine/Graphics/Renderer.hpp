#pragma once

#include <string>

#include "Shader/Shader.hpp"

#include "EGLManager.hpp"

namespace Engine
{
  class Renderer
  {
  public:
    Renderer(EGLManager& eglManager);
    ~Renderer();

    bool TryCreate();
    void Draw();
    void Update();
    void Destroy();

  private:
    EGLManager& m_EGLManager;
    Shader m_Shader;
    GLuint m_VertexBuffer;

    void SetupTriangle();
  };
}  // namespace Engine
