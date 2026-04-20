#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_

#include "game_object.h"

#include <vector>

namespace musashi {

struct GameLevel {
  std::vector<Zombie> zombies;
  void IsComplete();
  void Init();
  void Draw();
  void Load();
};

}  // namespace musashi

#endif
