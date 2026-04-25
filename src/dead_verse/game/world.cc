#include "global.h"
#include "object.h"
#include "player.h"
#include "world.h"
#include "zombie.h"

#include "entity/components.h"
#include "renderer/mesh.h"

namespace musashi {

World::World() {
  Init();
}

void World::Init() {
  InitPlayer("Wood");
  ObjectHandler::InitObject(*player_);
  for (int i = 0; i < level_handler_->zombie_count; ++i) {
    InitZombie("Zombie" + std::to_string(i));
    ObjectHandler::InitObject(level_handler_->level.zombies[i]);
  }
}

void World::InitPlayer(const std::string& name) {
  PlayerBuilder player_builder;

  // TransformComponent transform;
  // transform.position = glm::vec3(0.0f, 0.0f, -8.0f);
  // transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

  TagInputComponent input;

  player_ =
      std::move(player_builder
                    .Create(name)
                    // .WithComponent(std::move(transform))
                    .WithComponent<VelocityComponent>(VelocityComponent{0.05})
                    .WithComponent<TagInputComponent>(std::move(input))
                    .Build());
}

void World::InitZombie(const std::string& name) {
  ZombieBuilder zombie_builder;

  TransformComponent transform;
  transform.position = glm::vec3(0.0f, 0.0f, -8.0f);
  transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

  QuadComponent quad;
  quad.position = transform.position;
  quad.scale = transform.scale;
  quad.mesh = std::make_unique<Mesh>(Quad2D::data, Quad2D::indices);

  std::filesystem::path sprite_path{"assets/sprites/Zombie_1/Dead.png"};
  SpriteComponent sprite;
  sprite.sprite.source = std::make_shared<Texture>(sprite_path);
  sprite.sprite.data.slot = 0;
  sprite.sprite.data.name = "uZombie";

  auto zombie = zombie_builder.Create(name)
                    .WithComponent<TransformComponent>(std::move(transform))
                    .WithComponent<QuadComponent>(std::move(quad))
                    .WithComponent<SpriteComponent>(std::move(sprite))
                    .Build();
  level_handler_->level.zombies.emplace_back(std::move(zombie));
}

}  // namespace musashi
