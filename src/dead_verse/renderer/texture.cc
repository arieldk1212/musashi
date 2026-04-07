#include "global.h"
#include "texture.h"

#include <print>

#include <glad/glad.h>
#include <vendor/stb_image.h>

#include "util/log.h"

namespace musashi {

unsigned int Texture::AddTexture(const std::filesystem::path& texture_path,
                                 bool flip) {
  unsigned int new_texture{0};
  stbi_set_flip_vertically_on_load(flip);  // if it is flipped

  glGenTextures(1, &new_texture);
  glBindTexture(GL_TEXTURE_2D, new_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width{0};
  int height{0};
  int nr_channels{0};
  unsigned char* data =
      stbi_load(texture_path.c_str(), &width, &height, &nr_channels, 0);

  if (data != nullptr) {
    if (texture_path.extension() == ".png") {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, data);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    kGlobal.logger->Error("Failed to load texture");
  }

  stbi_image_free(data);

  kGlobal.logger->Trace("Added Texture Successfully");

  return new_texture;
}

}  // namespace musashi
