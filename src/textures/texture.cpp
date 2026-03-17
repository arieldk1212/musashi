#include <print>

#include "stb_image.h"
#include <glad/glad.h>

#include "textures/texture.h"

Texture::Texture(std::filesystem::path texturePath) {
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
  glGenTextures(1, &texture); // 1 is num of textures, and stores it inside the
                              // second parameter arr/single int.
  glBindTexture(GL_TEXTURE_2D, texture);
  if (data != nullptr) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::println("Failed to load texture");
  }
  stbi_image_free(data);
}