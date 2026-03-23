#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <filesystem>
#include <vector>

namespace Musashi {

class Texture {
public:
  Texture() = default;

  void AddTexture(std::filesystem::path texturePath, bool flip);
  int Size() const { return textures_.size(); }
  unsigned int Get(int idx) const { return textures_[idx]; }

private:
  std::vector<unsigned int> textures_;
};

} // namespace Musashi

#endif