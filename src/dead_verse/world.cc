#include "global.h"
#include "world.h"

#include "entity/component_manager.h"
#include "entity/components.h"

namespace musashi {

World::World() {
  InitTestEntity("Cube");
}

void World::InitTestEntity(const std::string& name) {
  auto cube_entity = kECManager->CreateEntity(name);

  auto& transform = kECManager->AddComponent<TransformComponent>(
      cube_entity.id, TransformComponent{});
  transform.position = glm::vec3(0.0f, 0.0f, -3.0f);
  transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

  kECManager->AddComponent<VelocityComponent>(cube_entity.id,
                                              VelocityComponent{0.05f});
  kECManager->AddComponent<TagInputComponent>(cube_entity.id,
                                              TagInputComponent{});
}

}  // namespace musashi
