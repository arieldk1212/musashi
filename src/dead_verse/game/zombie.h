#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "object.h"

#include <unordered_map>

#include <glm/vec2.hpp>

#include "entity/entity_manager.h"

namespace musashi {

enum class ZombieType : uint8_t {
  kMale,
  kFemale,
  kSkirtFemale,
  kBaldMale,
};

static const std::unordered_map<ZombieType, std::string>& ZombieTypeNameMap() {
  static const std::unordered_map<ZombieType, std::string> kZombieMap = {
      {ZombieType::kMale, "Male Zombie"},
      {ZombieType::kFemale, "Female Zombie"},
      {ZombieType::kSkirtFemale, "Skirt Female Zombie"},
      {ZombieType::kBaldMale, "Bald Male Zombie"}};
  return kZombieMap;
}

struct MaleZombie {
  ZombieType type{ZombieType::kMale};
  glm::vec2 default_coordinates{0, 7};
  std::array<int, 2> x_sprite_coordinates{13, 15};
  std::array<int, 2> y_sprite_coordinates{8, 7};
  // std::unordered_map<ObjectAnimation, std::pair<int, int>> animations = {
  //     {ObjectAnimation::kMove, {y_sprite_coordinates[1], 6}}};
  Animations animations;
};

struct Zombie : public Object {
  Entity entity;
  bool destroyed{false};

  void Destory() override { destroyed = true; }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

}  // namespace musashi

#endif
