#pragma once

#include <string>

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

    void OnResize(std::uint32_t new_width, std::uint32_t new_height) override;

  private:
    EGLManager* m_EGL;
    Shader m_Shader;
    GLuint m_VertexBuffer;

    void SetupTriangle();
  };
}  // namespace Engine
