#ifndef WORLD_H_
#define WORLD_H_

#include <string>

namespace musashi {

class World {
 public:
  World();

  void Update(float ts);

  void SpawnPlayer();
  void SpawnZombie();

  // Entity related
  static void Init();
  static void InitQuad(const std::string& name);
  static void InitQuad3D(const std::string& name);
};

}  // namespace musashi

#endif
