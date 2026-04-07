#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <filesystem>

namespace musashi {

struct Texture {
 public:
  Texture() = default;

  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;

  unsigned int AddTexture(const std::filesystem::path& texture_path, bool flip);
};

}  // namespace musashi

#endif
