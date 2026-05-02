#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "object.h"

#include "entity/entity_manager.h"

namespace musashi {

enum class ZombieType : uint8_t {
  // TODO: For each zombie type we need to create the sprite sheet coordinates
  // vector, something like that.
  // TODO: Also add base name.
  kFemale,
  kMale,
  kSkirtFemale,
  kBaldMale,
};

struct Zombie : public Object {
  Entity entity;
  bool destroyed{false};

  void Destory() override { destroyed = true; }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

}  // namespace musashi

#endif
