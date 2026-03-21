#include <print>

#include "stb_image.h"
#include <glad/glad.h>

#include "textures/texture.h"

void Texture::AddTexture(std::filesystem::path texturePath, bool flip) {
  unsigned int newTexture;
  stbi_set_flip_vertically_on_load(flip); // if it is flipped

  glGenTextures(1, &newTexture);
  glBindTexture(GL_TEXTURE_2D, newTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

  if (data != nullptr) {
    if (texturePath.extension() == ".png") {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, data);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::println("Failed to load texture");
  }

  stbi_image_free(data);

  textures_.push_back(newTexture);
  std::println("Added texture successfully");
}