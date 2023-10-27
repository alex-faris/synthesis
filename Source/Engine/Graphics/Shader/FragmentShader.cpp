
#include "FragmentShader.hpp"

#include <iostream>

Engine::FragmentShader::FragmentShader() : mShaderID(0)
{
}

Engine::FragmentShader::~FragmentShader()
{
}

bool Engine::FragmentShader::tryCreate(const std::string& kSource)
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

  mShaderID = shader;
  return true;
}

GLuint Engine::FragmentShader::getID() const
{
  return mShaderID;
}

void Engine::FragmentShader::destroy()
{
  glDeleteShader(mShaderID);
}
