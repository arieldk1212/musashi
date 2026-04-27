#ifndef OBJECT_H_
#define OBJECT_H_

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

struct ObjectHandler {
  static void InitObject(Object& object) { object.Init(); }
  static void DestroyObject(Object& object) { object.Destory(); }
};

// TODO: Implement the randomness when spawing on the screen.
static inline glm::vec3 RandomSpawnPosition() {
  glm::vec3 position;
  position.z = 0.0f;
  return position;
}

}  // namespace musashi

#endif
