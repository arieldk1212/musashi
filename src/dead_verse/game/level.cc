#include "level.h"

namespace musashi {

LevelHandler::LevelHandler()
    : level(std::make_unique<Level>()) {
  InitLevel();
}

void LevelHandler::InitLevel() const {
  level->Init(LevelStates::kPreLevel);
}

void LevelHandler::StartLevel() {
  if (level->state == LevelStates::kPreLevel) {
    level->state = LevelStates::kLevelBegin;
  }
}

void LevelHandler::ResetLevel() {
  level->Reset();
  level.reset();
}

void LevelHandler::IncreaseLevel() {
  ++current_level;
  zombie_count *= kZombieSpawnMultiplier;
  ResetLevel();
  InitLevel();
}

}  // namespace musashi
