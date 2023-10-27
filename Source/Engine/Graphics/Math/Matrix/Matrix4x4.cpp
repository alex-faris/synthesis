#include "Matrix4x4.hpp"

#include <cmath>

Engine::Matrix4x4::Matrix4x4()
{
  for (u8 i = 0; i < 4; ++i)
  {
    (*this)(i, i) = 1.0f;
  }
}

Engine::Matrix4x4::Matrix4x4(const Matrix<4, 4>& kMatrix4) : Matrix<4, 4>(kMatrix4)
{
  for (u8 i = 0; i < 4; ++i)
  {
    (*this)(i, i) = 1.0f;
  }
}

Engine::Matrix4x4 Engine::Matrix4x4::setPitch(f32 angle)
{
  Matrix4x4 rotation;

  f32 cos_theta = cos(angle);
  f32 sin_theta = sin(angle);

  rotation(0, 0) = 1.0F;
  rotation(1, 1) = cos_theta;
  rotation(1, 2) = -sin_theta;
  rotation(2, 1) = sin_theta;
  rotation(2, 2) = cos_theta;

  return rotation;
}

Engine::Matrix4x4 Engine::Matrix4x4::setYaw(f32 angle)
{
  Matrix4x4 rotation;

  f32 cos_theta = cos(angle);
  f32 sin_theta = sin(angle);

  rotation(0, 0) = cos_theta;
  rotation(0, 2) = sin_theta;
  rotation(1, 1) = 1.0F;
  rotation(2, 0) = -sin_theta;
  rotation(2, 2) = cos_theta;

  return rotation;
}

Engine::Matrix4x4 Engine::Matrix4x4::setRoll(f32 angle)
{
  Matrix4x4 rotation;

  f32 cos_theta = cos(angle);
  f32 sin_theta = sin(angle);

  rotation(0, 0) = cos_theta;
  rotation(0, 1) = -sin_theta;
  rotation(1, 0) = sin_theta;
  rotation(1, 1) = cos_theta;

  return rotation;
}

Engine::Matrix4x4 Engine::Matrix4x4::setRotation(f32 pitch_angle, f32 yaw_angle, f32 roll_angle)
{
  Matrix4x4 pitch = setPitch(pitch_angle);
  Matrix4x4 yaw = setYaw(yaw_angle);
  Matrix4x4 roll = setRoll(roll_angle);

  return yaw * pitch * roll;
}
