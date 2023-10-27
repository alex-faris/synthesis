#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Utilities/Utils.hpp"

#include "FragmentShader.hpp"
#include "VertexShader.hpp"

Engine::Shader::Shader() : mShaderProgram(0)
{
}

Engine::Shader::~Shader()
{
}

bool Engine::Shader::tryCreate(const std::string& kVertexPath, const std::string& kFragmentPath)
{
  std::string vertex_source = Engine::readFile(kVertexPath);
  std::string fragment_source = Engine::readFile(kFragmentPath);

  VertexShader vertex_shader;
  if (!vertex_shader.tryCreate(vertex_source))
  {
    return false;
  }

  FragmentShader fragment_shader;
  if (!fragment_shader.tryCreate(fragment_source))
  {
    return false;
  }

  if (!linkProgram(vertex_shader.getID(), fragment_shader.getID()))
  {
    std::cerr << "Failed to link shaders!" << std::endl;
    return false;
  }

  return true;
}

void Engine::Shader::use()
{
  glUseProgram(mShaderProgram);
}

GLuint Engine::Shader::getProgramID() const
{
  return mShaderProgram;
}

bool Engine::Shader::compileShader(const std::string& kSource, GLenum shader_type, GLuint& shader)
{
  shader = glCreateShader(shader_type);
  const char* kSrc = kSource.c_str();
  glShaderSource(shader, 1, &kSrc, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetShaderInfoLog(shader, sizeof(info_log - 1), nullptr, info_log);

    std::cerr << "Failed to compile shader!" << info_log << std::endl;
    return false;
  }

  return true;
}

bool Engine::Shader::linkProgram(GLuint vertex_shader, GLuint fragment_shader)
{
  mShaderProgram = glCreateProgram();
  glAttachShader(mShaderProgram, vertex_shader);
  glAttachShader(mShaderProgram, fragment_shader);
  glLinkProgram(mShaderProgram);

  GLint success;
  glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetProgramInfoLog(mShaderProgram, sizeof(info_log - 1), nullptr, info_log);

    std::cerr << "Failed to link shader program!" << std::endl;
    return false;
  }

  return true;
}

void Engine::Shader::destroy()
{
  if (mShaderProgram != 0)
  {
    glDeleteProgram(mShaderProgram);
  }
}
