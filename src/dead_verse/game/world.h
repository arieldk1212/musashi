#ifndef WORLD_H_
#define WORLD_H_

#include "game_object.h"

#include <string>
#include <vector>

namespace musashi {

static constexpr std::vector<std::pair<int, int>> kZombieSpawnLocations;

// INFO: Responsible for objects, game world related stuff
class World {
 public:
  World();

  void Init();
  void Update(float ts);

  void SpawnPlayer() const;
  void SpawnZombie() const;

  static void InitBaseEntity(const std::string& name,
                             bool third_dimension = false);

 private:
  // NOTE: Represents current level
  int level_{1};
  Player player_;
};

}  // namespace musashi

#endif
