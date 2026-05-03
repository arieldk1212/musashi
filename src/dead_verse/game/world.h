#ifndef WORLD_H_
#define WORLD_H_

#include "player.h"
#include "zombie.h"

#include <memory>
#include <string>

#include "entity/component_manager.h"
#include "game/level.h"
#include "game/state.h"
#include "renderer/resource_manager.h"
#include "util/log.h"

namespace musashi {

// TODO: Implement State Machine Here
class World {
 public:
  World(Logger* logger, ComponentManager* ec,
        ResourceManager* resource_manager);

  void Init();
  void Update(float ts);
  void Render(State& state);

  void InitTiles();
  void InitPlayer(const std::string& name);
  void InitZombie(const std::string& name);

  const std::vector<Zombie>& GetZombies() {
    return level_handler_->level->zombies;
  }

  [[nodiscard]] int GetLevelZombieCount() const {
    return static_cast<int>(level_handler_->zombie_count);
  }

 private:
  Logger* logger_;
  ComponentManager* ec_;
  std::unique_ptr<Player> player_;
  ResourceManager* resource_manager_;
  std::unique_ptr<LevelHandler> level_handler_;
};

}  // namespace musashi

#endif
