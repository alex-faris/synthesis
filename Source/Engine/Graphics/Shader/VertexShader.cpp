#include "VertexShader.hpp"

#include <iostream>

Engine::VertexShader::VertexShader() : m_ShaderID(0)
{
}

Engine::VertexShader::~VertexShader()
{
}

bool Engine::VertexShader::TryCreate(const std::string& kSource)
{
  GLuint shader = glCreateShader(GL_VERTEX_SHADER);
  const char* kSrc = kSource.c_str();
  glShaderSource(shader, 1, &kSrc, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetShaderInfoLog(shader, 512, nullptr, info_log);

    std::cerr << "Failed to compile vertex shader:\n" << info_log << std::endl;
    return false;
  }

  m_ShaderID = shader;
  return true;
}

GLuint Engine::VertexShader::GetID() const
{
  return m_ShaderID;
}

void Engine::VertexShader::Destroy()
{
  glDeleteShader(m_ShaderID);
}
