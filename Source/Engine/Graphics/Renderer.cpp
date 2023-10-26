#include "Renderer.hpp"

#include <iostream>

#include "Math/Matrix/Matrix4x4.hpp"


Engine::Renderer::Renderer(EGLManager* eglManager)
    : m_EGL(eglManager), m_VertexBuffer(0), m_Timer(), m_Angle(0.0F)
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

  Matrix4x4 rotation_matrix = Matrix4x4::SetYaw(m_Angle);
  GLint rotation_matrix_uniform =
  glGetUniformLocation(m_Shader.GetProgramID(), "u_rotation_matrix");
  if (rotation_matrix_uniform != 1)
  {
    glUniformMatrix4fv(rotation_matrix_uniform, 1, GL_FALSE, rotation_matrix.GetData());
  }

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
  m_Timer.Tick();
  m_Angle += 0.01F;

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

void Engine::Renderer::OnResize(u32 new_width, u32 new_height)
{
  glViewport(0, 0, new_width, new_height);
}

void Engine::Renderer::Destroy()
{
  glDeleteBuffers(1, &m_VertexBuffer);
}
