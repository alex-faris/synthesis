#pragma once

#include "Matrix.hpp"

namespace Engine
{
  class Matrix4x4 : public Matrix<4, 4>
  {
  public:
    Matrix4x4();
    Matrix4x4(const Matrix<4, 4>& kMatrix4);

    static Matrix4x4 SetPitch(f32 angle);
    static Matrix4x4 SetYaw(f32 angle);
    static Matrix4x4 SetRoll(f32 angle);
    static Matrix4x4 SetRotation(f32 x_angle, f32 y_angle, f32 z_angle);
  };
}  // namespace Engine
