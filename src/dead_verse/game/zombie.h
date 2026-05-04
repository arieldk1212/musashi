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
  Animations animations = {
      {ObjectAnimation::kIdle, {AnimationFrame{.origin{0, 7}}}},
      {ObjectAnimation::kMove,
       {AnimationFrame{.origin{6, 7}}, AnimationFrame{.origin{7, 7}},
        AnimationFrame{.origin{8, 7}}, AnimationFrame{.origin{9, 7}},
        AnimationFrame{.origin{10, 7}}, AnimationFrame{.origin{11, 7}},
        AnimationFrame{.origin{12, 7}}, AnimationFrame{.origin{13, 7}},
        AnimationFrame{.origin{14, 7}}, AnimationFrame{.origin{15, 7}}}}};
};

struct Zombie : public Object {
  Entity entity;
  bool destroyed{false};

  void Destory() override { destroyed = true; }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

}  // namespace musashi

#endif
