#include "global.h"
#include "world.h"

#include "entity/component_manager.h"
#include "entity/components.h"
#include "renderer/mesh.h"

namespace musashi {

World::World() {
  Init();
}

void World::SpawnPlayer() const {}

void World::SpawnZombie() const {
  InitBaseEntity("Zombie");
}

void World::Init() {
  SpawnZombie();
}

void World::InitBaseEntity(const std::string& name, bool third_dimension) {
  auto entity = kECManager->CreateEntity(name);

  auto& transform = kECManager->AddComponent<TransformComponent>(
      entity.id, TransformComponent{});
  transform.position = glm::vec3(0.0f, 0.0f, -8.0f);
  transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

  kECManager->AddComponent<VelocityComponent>(entity.id,
                                              VelocityComponent{0.05f});

  std::filesystem::path sprite_path{"assets/sprites/Zombie_1/Dead.png"};
  auto& sprite =
      kECManager->AddComponent<SpriteComponent>(entity.id, SpriteComponent{});
  sprite.sprite.source = std::make_shared<Texture>(sprite_path);
  sprite.sprite.data.slot = 0;
  sprite.sprite.data.name = "Zombie";

  auto& quad =
      kECManager->AddComponent<QuadComponent>(entity.id, QuadComponent{});
  quad.position = transform.position;
  quad.scale = transform.scale;
  if (third_dimension) {
    quad.mesh = std::make_unique<Mesh>(Quad3D::data, Quad3D::indices);
  }
  quad.mesh = std::make_unique<Mesh>(Quad2D::data, Quad2D::indices);
}

}  // namespace musashi
