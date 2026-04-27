#include "object.h"
#include "player.h"
#include "world.h"
#include "zombie.h"

#include <filesystem>

#include "entity/component_manager.h"
#include "renderer/mesh.h"

namespace musashi {

World::World(ComponentManager& ec)
    : ec_(&ec),
      level_handler_(std::make_unique<LevelHandler>()) {
  Init();
}

void World::Init() {
  InitPlayer("Wood");
  player_->Init();

  for (int i = 0; i < level_handler_->zombie_count; ++i) {
    InitZombie("Zombie" + std::to_string(i));
    ObjectHandler::InitObject(level_handler_->level.zombies[i]);
  }
}

void World::InitPlayer(const std::string& name) {
  // PlayerBuilder player_builder;
  EntityBuilder<Player> player_builder(*ec_);

  auto player =
      std::move(player_builder.Create(name)
                    .WithComponent<VelocityComponent>(VelocityComponent{0.05})
                    .WithComponent<TagInputComponent>(TagInputComponent{})
                    .Build());
  player_ = std::make_unique<Player>(std::move(player));
}

void World::InitZombie(const std::string& name) {
  EntityBuilder<Zombie> zombie_builder(*ec_);

  TransformComponent transform;
  transform.position = RandomSpawnPosition();
  transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

  QuadComponent quad;
  quad.position = transform.position;
  quad.scale = transform.scale;
  quad.mesh = std::make_unique<Mesh>(Quad2D::data, Quad2D::indices);

  // TODO: Change to animation
  std::filesystem::path sprite_path{"assets/sprites/Zombie_1/Dead.png"};
  SpriteComponent sprite;
  sprite.sprite.source = std::make_shared<Texture>(sprite_path);
  sprite.sprite.data.slot = 0;
  sprite.sprite.data.name = "uZombie";

  auto zombie = zombie_builder.Create(name)
                    .WithComponent<TagZombieComponent>(TagZombieComponent{})
                    .WithComponent<TransformComponent>(std::move(transform))
                    .WithComponent<QuadComponent>(std::move(quad))
                    .WithComponent<SpriteComponent>(std::move(sprite))
                    .Build();
  level_handler_->level.zombies.emplace_back(std::move(zombie));
}

}  // namespace musashi
