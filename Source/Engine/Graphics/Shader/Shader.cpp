#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Utilities/Utils.hpp"

#include "FragmentShader.hpp"
#include "VertexShader.hpp"

Engine::Shader::Shader() : m_ShaderProgram(0)
{
}

Engine::Shader::~Shader()
{
}

bool Engine::Shader::TryCreate(const std::string& kVertexPath, const std::string& kFragmentPath)
{
  std::string vertex_source = Engine::ReadFile(kVertexPath);
  std::string fragment_source = Engine::ReadFile(kFragmentPath);

  VertexShader vertex_shader;
  if (!vertex_shader.TryCreate(vertex_source))
  {
    return false;
  }

  FragmentShader fragment_shader;
  if (!fragment_shader.TryCreate(fragment_source))
  {
    return false;
  }

  if (!LinkProgram(vertex_shader.GetID(), fragment_shader.GetID()))
  {
    std::cerr << "Failed to link shaders!" << std::endl;
    return false;
  }

  return true;
}

void Engine::Shader::Use()
{
  glUseProgram(m_ShaderProgram);
}

GLuint Engine::Shader::GetProgramID() const
{
  return m_ShaderProgram;
}

bool Engine::Shader::CompileShader(const std::string& kSource, GLenum shader_type, GLuint& shader)
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

bool Engine::Shader::LinkProgram(GLuint vertex_shader, GLuint fragment_shader)
{
  m_ShaderProgram = glCreateProgram();
  glAttachShader(m_ShaderProgram, vertex_shader);
  glAttachShader(m_ShaderProgram, fragment_shader);
  glLinkProgram(m_ShaderProgram);

  GLint success;
  glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetProgramInfoLog(m_ShaderProgram, sizeof(info_log - 1), nullptr, info_log);

    std::cerr << "Failed to link shader program!" << std::endl;
    return false;
  }

  return true;
}

void Engine::Shader::Destroy()
{
  if (m_ShaderProgram != 0)
  {
    glDeleteProgram(m_ShaderProgram);
  }
}
