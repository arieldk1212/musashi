#ifndef OBJECT_H_
#define OBJECT_H_

#include <random>
#include <unordered_map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "entity/entity_manager.h"

namespace musashi {

enum class ObjectAnimation : uint8_t {
  kStatic,
  kIdle,
  kMove,
  kAttack,
  kHit,
  kShoot,
  kDead,
};

struct AnimationFrame {
  float elapsed{0.0f};
  float duration{0.5f};
  glm::vec2 origin;
};

using AnimationList = std::vector<AnimationFrame>;
using AnimationObject = std::unordered_map<ObjectAnimation, AnimationList>;
using AnimationPack = std::unordered_map<std::string, AnimationObject>;

class Animations {
 public:
  Animations() = default;

  void AddAnimationsPack(std::string pack, const AnimationObject& animations);
  void RemoveAnimationsPack(std::string_view pack);
  AnimationObject& GetAnimations(std::string_view pack);

 private:
  AnimationPack* animations_;
};

class Object {
 public:
  virtual ~Object() = default;

  virtual void Init() {}
  virtual void Destory() = 0;
  [[nodiscard]] virtual EntityId GetObjectId() const { return kNullEntity; };
};

static inline glm::vec3 RandomSpawnPosition() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<> distr(-10.0f, 0.0f);

  return glm::vec3{0.0f, 0.0f, distr(gen)};
}

}  // namespace musashi

#endif
