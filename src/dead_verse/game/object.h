#ifndef OBJECT_H_
#define OBJECT_H_

#include <random>

#include <glm/vec3.hpp>

#include "entity/entity_manager.h"

namespace musashi {

class Object {
 public:
  virtual ~Object() = default;

  virtual void Init() {}
  virtual void Destory() = 0;
  [[nodiscard]] virtual EntityId GetObjectId() const { return kNullEntity; };
};

// TODO: Implement the randomness when spawing on the screen.
static inline glm::vec3 RandomSpawnPosition() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distr(-10, 0);

  glm::vec3 position{0.0f, 0.0f, 0.0f};

  position.z = static_cast<float>(distr(gen));
  return position;
}

}  // namespace musashi

#endif
