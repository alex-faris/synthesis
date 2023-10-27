#pragma once

#include <string>

#include <GLES2/gl2.h>

namespace Engine
{
  class VertexShader
  {
  public:
    VertexShader();
    ~VertexShader();

    bool tryCreate(const std::string& sourceCode);
    GLuint getID() const;
    void destroy();

  private:
    GLuint mShaderID;
  };
}  // namespace Engine
