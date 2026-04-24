#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_

#include "game_object.h"

#include <vector>

namespace musashi {

static constexpr int kZombieStartCount{10};
static constexpr float kZombieSpawnMultiplier{0.5};

struct GameLevel {
  std::vector<Zombie> zombies;
  void IsComplete();
  void Init();
  void Draw();
  void Load();
};

}  // namespace musashi

#endif
