#ifndef LEVEL_H_
#define LEVEL_H_

#include "zombie.h"

#include <vector>

namespace musashi {

struct Level {
  std::vector<Zombie> zombies;
  bool state;

  void Init() {}
  void Draw() {}
  void Load() {}
  void Reset() {}
};

struct LevelHandler {
  Level level;
  int current_level{1};
  int zombie_count{kZombieStartCount};

  static constexpr int kZombieStartCount{10};
  static constexpr float kZombieSpawnMultiplier{0.5};

  LevelHandler();
  ~LevelHandler() = default;

  LevelHandler(const LevelHandler&) = delete;
  LevelHandler& operator=(const LevelHandler&) = delete;
  LevelHandler(LevelHandler&&) = delete;
  LevelHandler& operator=(LevelHandler&&) = delete;

  void InitLevel();
  void ResetLevel();
  void IncreaseLevel();
};

}  // namespace musashi

#endif
