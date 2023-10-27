#pragma once

#include <vector>

#include "Engine/Types.hpp"

namespace Engine
{
  template<u32 rows, u32 cols> class Matrix
  {
  public:
    Matrix() : mData(rows * cols, 0.0F)
    {
    }

    f32& operator()(u32 row, u32 column)
    {
      return mData[row * cols + column];
    }

    const f32& operator()(u32 row, u32 column) const
    {
      return mData[row * cols + column];
    }

    Matrix operator+(const Matrix& other) const
    {
      Matrix<rows, cols> sum;

      for (u32 i = 0; i < rows; ++i)
      {
        for (u32 j = 0; j < cols; ++j)
        {
          sum(i, j) = (*this)(i, j) + other(i, j);
        }
      }

      return sum;
    }

    Matrix operator-(const Matrix& other) const
    {
      Matrix<rows, cols> difference;

      for (u32 i = 0; i < rows; ++i)
      {
        for (u32 j = 0; j < cols; ++j)
        {
          difference(i, j) = (*this)(i, j) - other(i, j);
        }
      }

      return difference;
    }

    template<u32 resultCols, u32 commonDimension>
    Matrix operator*(const Matrix<commonDimension, resultCols>& other) const
    {
      Matrix<rows, resultCols> product;

      for (u32 i = 0; i < rows; ++i)
      {
        for (u32 j = 0; j < resultCols; ++j)
        {
          product(i, j) = 0;
          for (u32 k = 0; k < commonDimension; ++k)
          {
            product(i, j) += (*this)(i, k) * other(k, j);
          }
        }
      }

      return product;
    }

    const f32* getData() const
    {
      return mData.data();
    }

  protected:
    std::vector<f32> mData;
  };
}  // namespace Engine
