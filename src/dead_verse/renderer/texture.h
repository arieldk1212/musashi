#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <filesystem>

namespace musashi {

struct Texture {
  Texture(const std::filesystem::path& texture_path, bool flip);

  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;

  unsigned int id{0};
  int width{0};
  int height{0};
  int nr_channels{0};
};

}  // namespace musashi

#endif
