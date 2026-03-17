#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <filesystem>
#include <vector>

class Texture {
public:
  Texture() = default;

  void AddTexture(std::filesystem::path texturePath, bool flip);
  int Size() const { return textures_.size(); }
  unsigned int Get(int idx) { return textures_[idx]; }

private:
  std::vector<unsigned int> textures_;
};

#endif