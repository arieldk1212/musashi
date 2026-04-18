#ifndef WORLD_H_
#define WORLD_H_

#include <string>

namespace musashi {

class World {
 public:
  World();

  void Init();
  void Update(float ts);

  void SpawnPlayer();
  void SpawnZombie();

  static void InitTestEntity(const std::string& name);

 private:
  void InitBasicEntities();
};

}  // namespace musashi

#endif
