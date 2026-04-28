#include "texture.h"

#include <glad/glad.h>
#include <vendor/stb_image.h>

#include "util/log.h"

namespace musashi {

Texture::Texture(const std::filesystem::path& path) {
  stbi_set_flip_vertically_on_load(1);

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned char* data =
      stbi_load(path.c_str(), &width, &height, &nr_channels, 0);

  if (data != nullptr) {
    GLint format = GL_RGB;
    if (nr_channels == 4) {
      format = GL_RGBA;
    } else if (nr_channels == 1) {
      format = GL_RED;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);
}

Texture::~Texture() {
  glDeleteTextures(1, &id);
}

void Texture::Bind(uint32_t slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

}  // namespace musashi
