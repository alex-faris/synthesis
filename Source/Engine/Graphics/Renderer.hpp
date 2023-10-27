#pragma once

#include <string>

#include "Engine/Timer/Timer.hpp"
#include "Engine/Window/WindowObserver.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"

#include "EGLManager.hpp"

namespace Engine
{
  class Renderer : public WindowObserver
  {
  public:
    Renderer(EGLManager* egl);
    ~Renderer();

    bool tryCreate();
    void draw();
    void update();
    void destroy();

    void onResize(u32 newWidth, u32 newHeight) override;

  private:
    EGLManager* mEGL;
    Shader mShader;
    GLuint mVertexBuffer;
    Timer mTimer;
    f32 mAngle;
    Texture mTexture;

    void setupTriangle();
    void setupSquare();
  };
}  // namespace Engine
