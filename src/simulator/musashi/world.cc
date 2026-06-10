#include "world.h"

#include <string>

#include "entity/components.h"

namespace musashi {

World::World(Logger* logger, ComponentManager* ec,
             ResourceManager* resource_manager)
    : logger_(logger),
      ec_(ec),
      resource_manager_(resource_manager) {
  Init();
}

void World::InitLevel() {}

void World::InitTiles() {}

void World::Init() {
  InitTiles();

  InitPlayer("Wood");
  player_->Init();
}

void World::InitPlayer(const std::string& name) {
  EntityBuilder<Player> player_builder(*ec_);

  auto player = player_builder.Create(name)
                    .WithComponent<VelocityComponent>(VelocityComponent{0.05})
                    .WithComponent<TagInputComponent>(TagInputComponent{})
                    .Build();
  player_ = std::make_unique<Player>(std::move(player));
  logger_->Trace("Main Player Created");
}

// Commented for reference
// void World::InitZombie(ZombieType type, int i) {
//   EntityBuilder<Zombie> zombie_builder(*ec_);

//   TransformComponent transform;
//   transform.position = RandomSpawnPosition();
//   transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

//   QuadComponent quad;
//   quad.position = transform.position;
//   quad.scale = transform.scale;
//   quad.mesh = std::make_unique<Mesh>(Quad2D::kData, Quad2D::kIndices);

//   AnimationComponent animation;
//   animation.current_animation = ObjectAnimation::kHit;

//   SpriteComponent sprite;
//   sprite.sprite.source = resource_manager_->GetTexture(
//       ResourceManager::TextureName::kZombiesSheet);
//   sprite.sprite.data.slot = 0;
//   sprite.sprite.data.name = "uZombie";
//   sprite.sprite.data.size = {130, 126};
//   sprite.sprite.data.origin = GetZombieTypeStaticMap().at(type);

//   const auto& name = GetZombieTypeNameMap().at(type) + std::to_string(++i);
//   auto zombie = zombie_builder.Create(name)
//                     .WithComponent<QuadComponent>(std::move(quad))
//                     .WithComponent<TagZombieComponent>(TagZombieComponent{})
//                     .WithComponent<TransformComponent>(std::move(transform))
//                     .WithComponent<SpriteComponent>(std::move(sprite))
//                     .WithComponent<AnimationComponent>(std::move(animation))
//                     .Build();
//   zombie.type = type;

//   level_handler_->level->zombies.emplace_back(std::move(zombie));
//   logger_->Trace(name + " Created");
// }

}  // namespace musashi
