#ifndef PERLIN_NOISE_H_
#define PERLIN_NOISE_H_

#include <glm/vec3.hpp>

namespace musashi {

struct Coordinates {
  float x;
  float y;
};

struct PerlinNoise {
  static glm::vec3 GenerateNoise() {}

  static glm::vec3 GetNoiseLayer() {
    uint8_t frequency{1};
    uint8_t amplitude{1};
  }

  static glm::vec3 Calculate(Coordinates cords) {}
};

}  // namespace musashi

#endif
