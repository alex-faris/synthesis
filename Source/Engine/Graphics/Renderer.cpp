#include "Renderer.hpp"

#include <iostream>

Engine::Renderer::Renderer(EGLManager* eglManager) : m_EGL(eglManager), m_VertexBuffer(0)
{
}

Engine::Renderer::~Renderer()
{
}

bool Engine::Renderer::TryCreate()
{
  if (!m_Shader.TryCreate("Data/Shaders/TriangleVertex.glsl", "Data/Shaders/TriangleFragment.glsl"))
  {
    std::cerr << "Failed to create renderer!" << std::endl;
    return false;
  }

  SetupTriangle();
  return true;
}

void Engine::Renderer::Draw()
{
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT);

  glViewport(0, 0, m_EGL->GetSurfaceWidth(), m_EGL->GetSurfaceHeight());

  glUseProgram(m_Shader.GetProgramID());

  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

  GLint position_attribute = glGetAttribLocation(m_Shader.GetProgramID(), "in_position");
  if (position_attribute != -1)
  {
    glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(position_attribute);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(position_attribute);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}

void Engine::Renderer::Update()
{
  eglSwapBuffers(m_EGL->GetDisplay(), m_EGL->GetSurface());
}

void Engine::Renderer::SetupTriangle()
{
  GLfloat vertices[9] = {0.0F, 0.5F, 0.0F, 0.5F, -0.5F, 0.0F, -0.5F, -0.5F, 0.0F};

  glGenBuffers(1, &m_VertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::Renderer::OnResize(std::uint32_t new_width, std::uint32_t new_height)
{
  glViewport(0, 0, new_width, new_height);
}

void Engine::Renderer::Destroy()
{
  glDeleteBuffers(1, &m_VertexBuffer);
}
