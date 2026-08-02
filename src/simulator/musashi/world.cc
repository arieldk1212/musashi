#include "world.h"

#include <memory>
#include <string>

#include "entity/components.h"
#include "musashi/block.h"
#include "renderer/mesh.h"
#include "renderer/resource_manager.h"

namespace musashi {

World::World(Logger* logger, ComponentManager* ec,
             ResourceManager* resource_manager)
    : logger_(logger),
      ec_(ec),
      resource_manager_(resource_manager) {
  Init();
}

void World::Init() {
  InitTerrain();

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

void World::InitTerrain(size_t terrain_size) {
  EntityBuilder<Block> block_builder(*ec_);

  for (int i = 0; i < terrain_size; ++i) {
    InitChunk(block_builder);
  }
}

// Commented for reference
// void World::InitZombie(ZombieType type, int i) {

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
