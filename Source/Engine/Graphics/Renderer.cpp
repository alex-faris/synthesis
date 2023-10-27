#include "Renderer.hpp"

#include <iostream>

#include "Math/Matrix/Matrix4x4.hpp"


Engine::Renderer::Renderer(EGLManager* eglManager)
    : mEGL(eglManager), mVertexBuffer(0), mTimer(), mAngle(0.0F), mTexture()
{
}

Engine::Renderer::~Renderer()
{
}

bool Engine::Renderer::tryCreate()
{
  if (!mShader.tryCreate("Data/Shaders/TriangleVertex.glsl", "Data/Shaders/TriangleFragment.glsl"))
  {
    return false;
  }

  if (!mTexture.tryCreate("Data/Textures/Dummy.png"))
  {
    return false;
  }

  setupTriangle();
  // setupSquare();
  return true;
}

void Engine::Renderer::draw()
{
  mTexture.bind();

  glClearColor(0.1F, 0.1F, 0.1F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT);

  glViewport(0, 0, mEGL->getSurfaceWidth(), mEGL->getSurfaceHeight());

  glUseProgram(mShader.getProgramID());

  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

  Matrix4x4 rot_mat = Matrix4x4::setYaw(0.0);
  GLint rot_mat_u = glGetUniformLocation(mShader.getProgramID(), "u_rotation_matrix");
  if (rot_mat_u != -1)
  {
    glUniformMatrix4fv(rot_mat_u, 1, GL_FALSE, rot_mat.getData());
  }

  GLint pos_attr = glGetAttribLocation(mShader.getProgramID(), "in_position");
  GLint tex_coords_attr = glGetAttribLocation(mShader.getProgramID(), "in_texture_coordinates");

  if (pos_attr != -1 && tex_coords_attr != -1)
  {
    // Position
    glVertexAttribPointer(pos_attr, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(pos_attr);

    // Texture coordinates
    glVertexAttribPointer(tex_coords_attr, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(tex_coords_attr);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(pos_attr);
    glDisableVertexAttribArray(tex_coords_attr);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::Renderer::update()
{
  mTimer.tick();
  mAngle += 0.01F;

  eglSwapBuffers(mEGL->getDisplay(), mEGL->getSurface());
}

void Engine::Renderer::setupTriangle()
{
  GLfloat vertices[15] = {
  // Position         // Texture coordinates
  0.0F,   1.0F,  0.0F, 0.5F, 1.0F,  // Top center
  -0.55F, -1.0F, 0.0F, 0.0F, 0.0F,  // Bottom left
  0.55F,  -1.0F, 0.0F, 1.0F, 0.0F,  // Bottom right
  };

  glGenBuffers(1, &mVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Engine::Renderer::setupSquare()
{
  GLfloat vertices[30] = {
  // Position         // Texture coordinates
  -0.55F, 1.0F,  0.0F, 0.0F, 1.0F,  // Top left
  0.55F,  1.0F,  0.0F, 1.0F, 1.0F,  // Top right
  -0.55F, -1.0F, 0.0F, 0.0F, 0.0F,  // Bottom left

  -0.55F, -1.0F, 0.0F, 0.0F, 0.0F,  // Bottom left
  0.55F,  1.0F,  0.0F, 1.0F, 1.0F,  // Top right
  0.55F,  -1.0F, 0.0F, 1.0F, 0.0F,  // Bottom right
  };

  glGenBuffers(1, &mVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Engine::Renderer::onResize(u32 new_width, u32 new_height)
{
  glViewport(0, 0, new_width, new_height);
}

void Engine::Renderer::destroy()
{
  glDeleteBuffers(1, &mVertexBuffer);
}
