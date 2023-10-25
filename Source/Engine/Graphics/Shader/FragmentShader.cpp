
#include "FragmentShader.hpp"

#include <iostream>

Engine::FragmentShader::FragmentShader() : m_ShaderID(0)
{
}

Engine::FragmentShader::~FragmentShader()
{
}

bool Engine::FragmentShader::TryCreate(const std::string& kSource)
{
  GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* kSrc = kSource.c_str();
  glShaderSource(shader, 1, &kSrc, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetShaderInfoLog(shader, 512, nullptr, info_log);

    std::cerr << "Failed to compile fragment shader:\n" << info_log << std::endl;
    return false;
  }

  m_ShaderID = shader;
  return true;
}

GLuint Engine::FragmentShader::GetID() const
{
  return m_ShaderID;
}

void Engine::FragmentShader::Destroy()
{
  glDeleteShader(m_ShaderID);
}
