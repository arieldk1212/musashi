#ifndef BLOCK_H_
#define BLOCK_H_

#include "entity/entity_manager.h"
#include "musashi/object.h"

namespace musashi {

struct Block : public Object {
  Entity entity;
  bool destroyed{false};

  void Destory() override { destroyed = true; }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

struct Chunk {
  std::vector<std::vector<Block>> chunk;
};
// 1. Terrain Shaping - Empty blocks (stones, caves).
// 2. Water filling - below y..
// 3. Surface replacement.
// 4. Features & structures.

class Blocks {
 public:
  enum class BlockState : uint8_t { kGrass, kStone, kDirt };

  BlockState IdentifyBlock(const glm::vec3& coordinates);
  BlockState GetBlock(const glm::vec3& coordinates) {
    // random seed
    // random terrain height.. but with sine!
    // calculate sine with amplitude but also for z-axis.
    /**
     Example:
     float freq{0.1};
     int amp{1};
     float xoffset = (x * freq) * amp;
     float zoffset = (z * freq) * amp;
     float y_surface = 100 + xoffset + zoffset;
     */
    // return stone or air.
  }
};

}  // namespace musashi

#endif
