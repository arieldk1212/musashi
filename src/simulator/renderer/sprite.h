#ifndef SPRITE_H_
#define SPRITE_H_

#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "renderer/shader.h"
#include "renderer/texture.h"

namespace musashi {

struct SpriteData {
  glm::vec2 size;
  glm::vec2 origin;
  std::string name;
  uint32_t slot{0};
};

struct Sprite {
  SpriteData data;
  std::shared_ptr<Texture> source;

  void SetSprite(Shader& shader) const {
    shader.SetInt(data.name, data.slot);
    source->Bind(data.slot);
  }
};

}  // namespace musashi

#endif
