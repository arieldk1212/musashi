#ifndef WORLD_H_
#define WORLD_H_

#include "player.h"
#include "zombie.h"

#include <memory>
#include <string>

#include "entity/component_manager.h"
#include "game/level.h"
#include "game/state.h"

namespace musashi {

// TODO: Implement State Machine Here
class World {
 public:
  explicit World(ComponentManager& ec);

  // INFO: Init first level
  void Init();
  void Update(float ts);
  void Render(State& state);

  void InitPlayer(const std::string& name);
  void InitZombie(const std::string& name);

  const std::vector<Zombie>& GetZombies() {
    return level_handler_->level.zombies;
  }

  [[nodiscard]] int GetZombieCount() const {
    return level_handler_->zombie_count;
  }

 private:
  ComponentManager* ec_;
  std::unique_ptr<Player> player_;
  std::unique_ptr<LevelHandler> level_handler_;
};

}  // namespace musashi

#endif
