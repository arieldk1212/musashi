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
  static auto& GetAnimations() {
    static const Animations kMaleZombieAnimations = {
        {ObjectAnimation::kMove,
         {AnimationFrame{.origin{6, 7}}, AnimationFrame{.origin{7, 7}},
          AnimationFrame{.origin{8, 7}}, AnimationFrame{.origin{9, 7}},
          AnimationFrame{.origin{10, 7}}, AnimationFrame{.origin{11, 7}},
          AnimationFrame{.origin{12, 7}}, AnimationFrame{.origin{13, 7}},
          AnimationFrame{.origin{14, 7}}, AnimationFrame{.origin{15, 7}}}}};
    return kMaleZombieAnimations;
  }
};

struct FemaleZombieAnimations {
  static auto& GetFemaleZombieAnimations() {
    static const Animations kFemaleZombieAnimations = {};
    return kFemaleZombieAnimations;
  }
};

struct BaldMaleZombieAnimations {
  static auto& GetBaldMaleZombieAnimations() {
    static const Animations kBaldMaleZombieAnimations = {};
    return kBaldMaleZombieAnimations;
  }
};

struct SkirtFemaleZombieAnimations {
  static auto& GetSkirtFemaleZombieAnimations() {
    static const Animations kSkirtFemaleZombieAnimations = {};
    return kSkirtFemaleZombieAnimations;
  }
};

}  // namespace zombie_animations

struct Zombie : public Object {
  Entity entity;
  bool destroyed{false};

  void Destory() override { destroyed = true; }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

}  // namespace musashi

#endif
