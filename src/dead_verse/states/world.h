#ifndef WORLD_H_
#define WORLD_H_

namespace musashi {

class World {
 public:
  World();

  void Update();
  void Tick();

  void UpdatePlayer();
  void UpdateZombies();
  void UpdateWeapons();
  void UpdateRandomGenerator();
};

}  // namespace musashi

#endif
