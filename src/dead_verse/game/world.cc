#include "global.h"
#include "world.h"

#include "entity/component_manager.h"
#include "entity/components.h"
#include "renderer/mesh.h"

namespace musashi {

World::World() {
  Init();
}

void World::Init() {
  InitQuad("Quad2D");
  InitQuad3D("Quad3D");
}

void World::InitQuad(const std::string& name) {
  auto quad_entity = kECManager->CreateEntity(name);

  auto& transform = kECManager->AddComponent<TransformComponent>(
      quad_entity.id, TransformComponent{});
  transform.position = glm::vec3(0.0f, 0.0f, 8.0f);
  transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

  kECManager->AddComponent<VelocityComponent>(quad_entity.id,
                                              VelocityComponent{0.05f});
  kECManager->AddComponent<TagInputComponent>(quad_entity.id,
                                              TagInputComponent{});

  auto& quad =
      kECManager->AddComponent<QuadComponent>(quad_entity.id, QuadComponent{});
  quad.position = transform.position;
  quad.scale = transform.scale;
  quad.mesh = std::make_unique<Mesh>(Quad2D::data, Quad2D::indices);
}

void World::InitQuad3D(const std::string& name) {
  auto quad_entity = kECManager->CreateEntity(name);

  auto& transform = kECManager->AddComponent<TransformComponent>(
      quad_entity.id, TransformComponent{});
  transform.position = glm::vec3(0.0f, 0.0f, 10.0f);
  transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

  kECManager->AddComponent<VelocityComponent>(quad_entity.id,
                                              VelocityComponent{0.05f});
  kECManager->AddComponent<TagInputComponent>(quad_entity.id,
                                              TagInputComponent{});

  auto& quad =
      kECManager->AddComponent<QuadComponent>(quad_entity.id, QuadComponent{});
  quad.position = transform.position;
  quad.scale = transform.scale;
  quad.mesh = std::make_unique<Mesh>(Quad3D::data, Quad3D::indices);
}

}  // namespace musashi
