#ifndef OBJECT_H_
#define OBJECT_H_

#include <glm/vec2.hpp>

#include "entity/entity_manager.h"

namespace musashi {

class Object {
 public:
  virtual ~Object() = default;

  virtual void Init() = 0;
  virtual void Destory() = 0;
  [[nodiscard]] virtual EntityId GetObjectId() const { return kNullEntity; };
};

struct ObjectHandler {
  static void InitObject(Object& object) { object.Init(); }
  static void DestroyObject(Object& object) { object.Destory(); }
};

}  // namespace musashi

#endif
