#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <filesystem>
class Texture {
public:
  Texture(std::filesystem::path texturePath);

  unsigned int texture;

private:
};

#endif