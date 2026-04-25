#ifndef WORLD_H_
#define WORLD_H_

#include "objects.h"

#include <memory>
#include <string>

#include "game/level.h"
#include "game/state.h"

namespace musashi {

// TODO: Implement State Machine Here
class World {
 public:
  World();

  // INFO: Init first level
  void Init();
  void Update(float ts);
  void Render(State& state);

  void InitPlayer(const std::string& name);
  void InitZombie(const std::string& name);

 private:
  std::unique_ptr<Player> player_;
  std::unique_ptr<LevelHandler> level_handler_;
};

}  // namespace musashi

#endif
