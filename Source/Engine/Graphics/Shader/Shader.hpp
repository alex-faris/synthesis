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

    bool tryCreate(const std::string& vertexPath, const std::string& fragmentPath);
    void use();
    GLuint getProgramID() const;
    void destroy();

  private:
    GLuint mShaderProgram;

    bool compileShader(const std::string& sourceCode, GLenum shaderType, GLuint& shader);
    bool linkProgram(GLuint vertexShader, GLuint fragmentShader);
  };
}  // namespace Engine
