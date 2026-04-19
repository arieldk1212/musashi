#ifndef SPRITE_H_
#define SPRITE_H_

#include <glm/vec2.hpp>

namespace musashi {

struct Sprite {
  size_t size;
  glm::vec2 origin;
};

}  // namespace musashi

#endif
