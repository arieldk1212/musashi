#include "object.h"
#include "world.h"

#include "entity/components.h"
#include "game/zombie.h"

namespace musashi {

World::World(Logger* logger, ComponentManager* ec,
             ResourceManager* resource_manager)
    : logger_(logger),
      ec_(ec),
      resource_manager_(resource_manager),
      level_handler_(std::make_unique<LevelHandler>()) {
  Init();
}

void World::InitTiles() {}

void World::Init() {
  InitTiles();

  InitPlayer("Wood");
  player_->Init();
  logger_->Trace("Player Created");

  for (int i = 0; i < GetLevelZombieCount(); ++i) {
    InitZombie("Zombie" + std::to_string(i));
    logger_->Trace("Zombie Created");
  }
}

void World::InitPlayer(const std::string& name) {
  EntityBuilder<Player> player_builder(*ec_);

  auto player = player_builder.Create(name)
                    .WithComponent<VelocityComponent>(VelocityComponent{0.05})
                    .WithComponent<TagInputComponent>(TagInputComponent{})
                    .Build();
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
  quad.mesh = std::make_unique<Mesh>(Quad2D::kData, Quad2D::kIndices);

  // TODO: Here init default sprite coordinates for specific zombie type.
  SpriteComponent sprite;
  sprite.sprite.source = resource_manager_->GetTexture(
      ResourceManager::TextureName::kZombiesSheet);
  sprite.sprite.data.slot = 0;
  sprite.sprite.data.name = "uZombie";
  sprite.sprite.data.size = {126, 126};
  sprite.sprite.data.origin = {6, 7};

  AnimationComponent animation;

  auto zombie = zombie_builder.Create(name)
                    .WithComponent<QuadComponent>(std::move(quad))
                    .WithComponent<TagZombieComponent>(TagZombieComponent{})
                    .WithComponent<TransformComponent>(std::move(transform))
                    .WithComponent<SpriteComponent>(std::move(sprite))
                    .WithComponent<AnimationComponent>(AnimationComponent{})
                    .Build();
  level_handler_->level->zombies.emplace_back(std::move(zombie));
}

}  // namespace musashi
