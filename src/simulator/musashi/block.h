#ifndef BLOCK_H_
#define BLOCK_H_

#include "entity/entity_manager.h"
#include "musashi/object.h"

namespace musashi {

enum class BlockState : uint8_t { kGrass, kStone, kDirt };

struct Block : public Object {
  Entity entity;
  bool destroyed{false};
  BlockState state{BlockState::kDirt};
  glm::vec3 coordinates;

  void Destory() override { destroyed = true; }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

struct Layer {
  std::vector<std::vector<Block>> layer;
};

struct Chunk {
  uint16_t id;
  std::vector<Layer> chunk;
};

template <size_t ChunksSize, size_t ChunkSize>
class Terrain {
 public:
  Terrain() {
    chunks_.reserve(ChunksSize);
    for (auto& chunk : chunks_) {
      chunk.chunk.reserve(ChunkSize);
    }
  }

 private:
  size_t number_of_chunks_;
  std::vector<Chunk> chunks_;
};

// 1. Terrain Shaping - Empty blocks (stones, caves).
// 2. Water filling - below y..
// 3. Surface replacement.
// 4. Features & structures.

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
struct BlockInformation {
  static BlockState IdentifyBlock(Block* block) { return block->state; }
  static bool GetBlock(Block* block) { return block->entity.IsDestroyed(); }
};

}  // namespace musashi

#endif
