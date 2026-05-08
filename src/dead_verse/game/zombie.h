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
  kBaldMale,
  kSkirtFemale,
};

inline auto& GetZombieTypeStaticMap() {
  static const std::unordered_map<ZombieType, glm::vec2> kZombieStaticMap = {
      {ZombieType::kMale, glm::vec2{0, 7}},
      {ZombieType::kFemale, glm::vec2{0, 5}},
      {ZombieType::kBaldMale, glm::vec2{0, 3}},
      {ZombieType::kSkirtFemale, glm::vec2{0, 0}}};
  return kZombieStaticMap;
}

inline auto& GetZombieTypeNameMap() {
  static const std::unordered_map<ZombieType, std::string> kZombieMap = {
      {ZombieType::kMale, "Male Zombie"},
      {ZombieType::kFemale, "Female Zombie"},
      {ZombieType::kBaldMale, "Bald Male Zombie"},
      {ZombieType::kSkirtFemale, "Skirt Female Zombie"}};
  return kZombieMap;
}

namespace zombie_animations {

struct MaleZombieAnimations {
  static auto& GetMaleAnimations() {
    static Animations kMaleZombieAnimations = {
        {ObjectAnimation::kMove,
         {AnimationFrame{.origin{6, 7}}, AnimationFrame{.origin{7, 7}},
          AnimationFrame{.origin{8, 7}}, AnimationFrame{.origin{9, 7}},
          AnimationFrame{.origin{10, 7}}, AnimationFrame{.origin{11, 7}},
          AnimationFrame{.origin{12, 7}}, AnimationFrame{.origin{13, 7}},
          AnimationFrame{.origin{14, 7}}, AnimationFrame{.origin{15, 7}}}},
        {ObjectAnimation::kIdle,
         {AnimationFrame{.duration = 1.0f, .origin{0, 7}},
          {AnimationFrame{.duration = 1.0f, .origin{0, 8}}}}},
        {ObjectAnimation::kAttack,
         {AnimationFrame{.duration = 0.8, .origin{0, 8}},
          AnimationFrame{.origin{1, 8}}, AnimationFrame{.origin{2, 8}},
          AnimationFrame{.origin{3, 8}}, AnimationFrame{.origin{4, 8}}}},
        {ObjectAnimation::kHit,
         {AnimationFrame{.duration = 0.8, .origin{10, 8}},
          AnimationFrame{.origin{11, 8}}, AnimationFrame{.origin{12, 8}},
          AnimationFrame{.origin{13, 8}}}},
        {ObjectAnimation::kDead,
         {AnimationFrame{.origin{5, 8}}, AnimationFrame{.origin{6, 8}},
          AnimationFrame{.origin{7, 8}}, AnimationFrame{.origin{8, 8}},
          AnimationFrame{.origin{9, 8}}}}};
    return kMaleZombieAnimations;
  }
};

struct FemaleZombieAnimations {
  static auto& GetFemaleZombieAnimations() {
    static Animations kFemaleZombieAnimations = {};
    return kFemaleZombieAnimations;
  }
};

struct BaldMaleZombieAnimations {
  static auto& GetBaldMaleZombieAnimations() {
    static Animations kBaldMaleZombieAnimations = {};
    return kBaldMaleZombieAnimations;
  }
};

struct SkirtFemaleZombieAnimations {
  static auto& GetSkirtFemaleZombieAnimations() {
    static Animations kSkirtFemaleZombieAnimations = {};
    return kSkirtFemaleZombieAnimations;
  }
};

static inline Animations& GetZombieAnimations(ZombieType type) {
  switch (type) {
    case ZombieType::kMale:
      return MaleZombieAnimations::GetMaleAnimations();
      break;
    case ZombieType::kFemale:
      return FemaleZombieAnimations::GetFemaleZombieAnimations();
      break;
    case ZombieType::kBaldMale:
      return BaldMaleZombieAnimations::GetBaldMaleZombieAnimations();
      break;
    case ZombieType::kSkirtFemale:
      return SkirtFemaleZombieAnimations::GetSkirtFemaleZombieAnimations();
      break;
  }
}

}  // namespace zombie_animations

struct Zombie : public Object {
  Entity entity;
  ZombieType type;
  bool destroyed{false};

  void Destory() override { destroyed = true; }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

}  // namespace musashi

#endif
