#ifndef SPRITE_H_
#define SPRITE_H_

#include <array>
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "renderer/texture.h"

namespace musashi {

struct Sprite {
  std::shared_ptr<Texture> source;
  glm::vec2 size;
  glm::vec2 origin;
  uint32_t slot;
  std::string name;
};

struct RenderedSprite {
  std::shared_ptr<Texture> sheet;
  std::array<glm::vec2, 4> uvs;
};

}  // namespace musashi

#endif
