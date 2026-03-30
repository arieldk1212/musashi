#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <filesystem>
#include <vector>

namespace musashi {

class Texture {
 public:
  Texture() = default;

  unsigned int AddTexture(const std::filesystem::path& texture_path, bool flip);
  [[nodiscard]] int Size() const { return static_cast<int>(textures_.size()); }
  [[nodiscard]] unsigned int Get(int idx) const { return textures_[idx]; }

 private:
  std::vector<unsigned int> textures_;
};

}  // namespace musashi

#endif