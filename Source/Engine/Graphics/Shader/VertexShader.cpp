#include "VertexShader.hpp"

#include <iostream>

Engine::VertexShader::VertexShader() : mShaderID(0)
{
}

Engine::VertexShader::~VertexShader()
{
}

bool Engine::VertexShader::tryCreate(const std::string& kSource)
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

  mShaderID = shader;
  return true;
}

GLuint Engine::VertexShader::getID() const
{
  return mShaderID;
}

void Engine::VertexShader::destroy()
{
  glDeleteShader(mShaderID);
}
