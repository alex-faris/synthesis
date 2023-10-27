#pragma once

#include <string>

#include <GLES2/gl2.h>

#include "Engine/Types.hpp"

namespace Engine
{
  class Texture
  {
  public:
    Texture();
    ~Texture();

    b8 tryCreate(const std::string& imagePath);
    void destroy();

    void bind(GLuint slot = 0) const;
    void unbind() const;

  private:
    GLuint mTextureID;
    s32 mWidth;
    s32 mHeight;

    b8 loadImage(const std::string& imagePath, unsigned char** data, s32* width, s32* height);
    void freeImage(unsigned char* data);
  };
}  // namespace Engine
