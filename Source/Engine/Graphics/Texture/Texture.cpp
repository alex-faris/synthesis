#include "Texture.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Engine::Texture::Texture() : mTextureID(0), mWidth(0), mHeight(0)
{
}

Engine::Texture::~Texture()
{
}

b8 Engine::Texture::tryCreate(const std::string& kImagePath)
{
  unsigned char* image_data;
  s32 width;
  s32 height;
  if (!loadImage(kImagePath, &image_data, &width, &height))
  {
    std::cerr << "Failed to create texture!" << std::endl;
    return false;
  }

  glGenTextures(1, &mTextureID);
  glBindTexture(GL_TEXTURE_2D, mTextureID);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);

  freeImage(image_data);
  mWidth = width;
  mHeight = height;

  return true;
}

b8 Engine::Texture::loadImage(const std::string& kImagePath, unsigned char** data, s32* width,
                              s32* height)
{
  s32 channels;
  *data = stbi_load(kImagePath.c_str(), width, height, &channels, STBI_rgb_alpha);
  if (!*data)
  {
    std::cout << "Failed to create texture channels!" << std::endl;
    return false;
  }

  return true;
}

void Engine::Texture::bind(GLuint slot) const
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Engine::Texture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::Texture::freeImage(unsigned char* data)
{
  stbi_image_free(data);
}

void Engine::Texture::destroy()
{
  if (!mTextureID)
  {
    glDeleteTextures(1, &mTextureID);
    mTextureID = 0;
  }

  mWidth = 0;
  mHeight = 0;
}
