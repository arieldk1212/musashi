#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <filesystem>

namespace musashi {

struct Texture {
  int width{0};
  int height{0};
  int nr_channels{0};
  unsigned int id{0};

  explicit Texture(const std::filesystem::path& path);
  ~Texture();

  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;

  void Bind(uint32_t slot) const;
  static void Unbind();
};

}  // namespace musashi

#endif
