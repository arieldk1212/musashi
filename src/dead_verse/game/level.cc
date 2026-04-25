#include "level.h"

namespace musashi {

LevelHandler::LevelHandler() {
  InitLevel();
}

void LevelHandler::InitLevel() {
  level.Init();
}

void LevelHandler::ResetLevel() {
  level.Reset();
}

void LevelHandler::IncreaseLevel() {
  ++current_level;
}

}  // namespace musashi
