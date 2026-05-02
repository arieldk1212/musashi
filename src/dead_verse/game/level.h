#ifndef LEVEL_H_
#define LEVEL_H_

#include "zombie.h"

#include <vector>

namespace musashi {

enum class LevelStates : uint8_t { kPreLevel, kLevelBegin, kLevelEnd };

struct Level {
  std::vector<Zombie> zombies;
  LevelStates state{LevelStates::kPreLevel};

  void Init(LevelStates init_state) { state = init_state; }
  void Reset() { zombies.clear(); }
};

struct LevelHandler {
  std::unique_ptr<Level> level;
  int current_level{1};
  float zombie_count{kZombieStartCount};

  static constexpr int kZombieDebugCount{1};
  static constexpr int kZombieStartCount{10};
  static constexpr float kZombieSpawnMultiplier{1.5};

  LevelHandler();
  ~LevelHandler() = default;

  LevelHandler(const LevelHandler&) = delete;
  LevelHandler& operator=(const LevelHandler&) = delete;
  LevelHandler(LevelHandler&&) = delete;
  LevelHandler& operator=(LevelHandler&&) = delete;

  void InitLevel() const;
  void StartLevel();
  void ResetLevel();
  void IncreaseLevel();
};

}  // namespace musashi

#endif
