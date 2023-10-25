#pragma once

#include <string>

#include <GLES2/gl2.h>

namespace Engine
{
  class FragmentShader
  {
  public:
    FragmentShader();
    ~FragmentShader();

    bool TryCreate(const std::string& kSource);
    GLuint GetID() const;
    void Destroy();

  private:
    GLuint m_ShaderID;
  };
}  // namespace Engine
