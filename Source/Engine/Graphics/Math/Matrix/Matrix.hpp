#pragma once

#include <vector>

#include "Engine/Types.hpp"

namespace Engine
{
  template<u32 rows, u32 columns> class Matrix
  {
  public:
    Matrix() : m_Data(rows * columns, 0.0F)
    {
    }

    f32& operator()(u32 row, u32 column)
    {
      return m_Data[row * columns + column];
    }

    const f32& operator()(u32 row, u32 column) const
    {
      return m_Data[row * columns + column];
    }

    Matrix operator+(const Matrix& kOther) const
    {
      Matrix<rows, columns> sum;

      for (u32 i = 0; i < rows; ++i)
      {
        for (u32 j = 0; j < columns; ++j)
        {
          sum(i, j) = (*this)(i, j) + kOther(i, j);
        }
      }

      return sum;
    }

    Matrix operator-(const Matrix& kOther) const
    {
      Matrix<rows, columns> difference;

      for (u32 i = 0; i < rows; ++i)
      {
        for (u32 j = 0; j < columns; ++j)
        {
          difference(i, j) = (*this)(i, j) - kOther(i, j);
        }
      }

      return difference;
    }

    template<u32 result_columns, u32 common_dimension>
    Matrix operator*(const Matrix<common_dimension, result_columns>& kOtherA) const
    {
      Matrix<rows, result_columns> product;

      for (u32 i = 0; i < rows; ++i)
      {
        for (u32 j = 0; j < result_columns; ++j)
        {
          product(i, j) = 0;
          for (u32 k = 0; k < common_dimension; ++k)
          {
            product(i, j) += (*this)(i, k) * kOtherA(k, j);
          }
        }
      }

      return product;
    }

    const f32* GetData() const
    {
      return m_Data.data();
    }

  protected:
    std::vector<f32> m_Data;
  };
}  // namespace Engine
