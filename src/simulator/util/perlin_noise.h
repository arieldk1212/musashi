#ifndef PERLIN_NOISE_H_
#define PERLIN_NOISE_H_

#include "rnd.h"

#include <glm/vec3.hpp>

namespace musashi {

struct Coordinates {
  glm::vec2 cords;
};

class PerlinNoise {
  PerlinNoise() = default;

  static float Interpolate(float a0, float a1, float w) {
    return static_cast<float>(((a1 - a0) * (3.0 - (w * 2.0)) * w * w) + a0);
  }

  static float DotGridGradient(const glm::vec2& distance, Coordinates cords) {
    glm::vec2 gradient = GenerateRandomGradient(cords.cords.x, cords.cords.y);

    float dx = distance.x - cords.cords.x;
    float dy = distance.y - cords.cords.y;

    return ((dx * gradient.x) + (dy * gradient.y));
  }

  static float Perlin(Coordinates cords) {
    // Determine grid cell corner coordinates
    int x0 = static_cast<int>(cords.cords.x);
    int x1 = x0 + 1;
    int y0 = static_cast<int>(cords.cords.y);
    int y1 = y0 + 1;

    // Compute interpolation weights
    float sx = cords.cords.x - static_cast<float>(x0);
    float sy = cords.cords.y - static_cast<float>(y0);

    // Compute and interpolate top two corners
    auto n0 = DotGridGradient(glm::vec2{x0, y0}, cords);
    auto n1 = DotGridGradient(glm::vec2{x1, y0}, cords);
    auto ix0 = Interpolate(n0, n1, sx);

    // Compute and interpolate bottom two corners
    n0 = DotGridGradient(glm::vec2{x0, y1}, cords);
    n1 = DotGridGradient(glm::vec2{x1, y1}, cords);
    auto ix1 = Interpolate(n0, n1, sx);

    float value = Interpolate(ix0, ix1, sy);

    return value;
  }
};

/**
 * @brief Example API Usage

 void TerrainGeneration(Window& window) {
    static constexpr kGridSize{400}; // Debug this.
    std::pair<float> window_sizes = window.GetSize();
    std::array<int, window_sizes.first * window_sizes.second * 4> pixels{0};

    for (int i = 0; i < window_sizes.first; ++i) { // Width
      for (int j = 0; j < window_sizes.second; ++j) { // Height

        int idx = (j * window_sizes.second + i) * 4;

        float amp{1};
        float freq{1};
        float perlin{0};

        static constexpr int kNoiseConsistency{12};

        for (int k = 0; k < kNoiseConsistency; ++k) {
          val += PerlinNoise::Perlin(i * freq / kGridSize, y * freq / kGridSize)
            * amp;
            freq *= 2;
            amp /= 2;
        }

        // Contrast
        val *= 1.2;

        // Clipping
        if (val > 1.0f) {
          val = 1.0f;
        }
        if (val < -1.0f) {
          val = -1.0f;
        }

        int color = static_cast<int>(((val + 1.0f) * 0.5f) * 255);

        pixels[idx] = color;
        pixels[idx + 1] = color;
        pixels[idx + 2] = color;
        pixels[idx + 3] = 255;
      }
    }
 }
 */

}  // namespace musashi

#endif
