#ifndef RND_H_
#define RND_H_

#include <cmath>
#include <numbers>

#include "glm/vec2.hpp"

namespace musashi {

static constexpr size_t kUnsignedSize = sizeof(unsigned);

static inline glm::vec2 GenerateRandomGradient(float ix, float iy) {
  constexpr unsigned kW = 8 * sizeof(unsigned);
  constexpr unsigned kS = kW / 2;
  unsigned a = ix;
  unsigned b = iy;

  a *= 3284157443;

  b ^= a << kS | a >> (kW - kS);
  b *= 1911520717;

  a ^= b << kS | b >> (kW - kS);
  a *= 2048419325;
  float random = a * (std::numbers::pi / ~(~0u >> 1));

  // Create the vector from the angle
  glm::vec2 vec;
  vec.x = std::sin(random);
  vec.y = std::cos(random);

  return vec;
}

}  // namespace musashi

#endif
