#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "object.h"

#include "entity/entity_manager.h"

namespace musashi {

struct Zombie : public Object {
  Entity entity;
  bool destroyed{false};

  void Destory() override { destroyed = true; }
  // void Transform(const glm::vec3& position) const {
  //   auto& transform =
  //   kECManager->GetComponent<TransformComponent>(entity.id);
  //   transform.position = position;
  // }

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

}  // namespace musashi

#endif
