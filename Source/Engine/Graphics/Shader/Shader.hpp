#pragma once

#include <string>

#include <GLES2/gl2.h>

namespace Engine
{
  class Shader
  {
  public:
    Shader();
    ~Shader();

    bool TryCreate(const std::string& kVertexPath, const std::string& kFragmentPath);
    void Use();
    GLuint GetProgramID() const;
    void Destroy();

  private:
    GLuint m_ShaderProgram;

    bool CompileShader(const std::string& kSource, GLenum shader_type, GLuint& shader);
    bool LinkProgram(GLuint vertex_shader, GLuint fragment_shader);
  };
}  // namespace Engine
