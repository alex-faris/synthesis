#pragma once

#include "Matrix.hpp"

namespace Engine
{
  class Matrix4x4 : public Matrix<4, 4>
  {
  public:
    Matrix4x4();
    Matrix4x4(const Matrix<4, 4>& matrix4x4);

    static Matrix4x4 setPitch(f32 angle);
    static Matrix4x4 setYaw(f32 angle);
    static Matrix4x4 setRoll(f32 angle);
    static Matrix4x4 setRotation(f32 xAngle, f32 yAngle, f32 zAngle);
  };
}  // namespace Engine
