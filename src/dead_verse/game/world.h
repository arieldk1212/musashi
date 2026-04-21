#ifndef WORLD_H_
#define WORLD_H_

#include "game_object.h"

#include <string>
#include <vector>

#include "renderer/mesh.h"

namespace musashi {

// INFO: Responsible for objects, game world related stuff
class World {
 public:
  World();

  void Update(float ts);

  void SpawnQuad(GameObjectData data);
  void SpawnPlayer();
  void SpawnZombie();

  // Entity related
  static void Init();
  static void InitQuad(const std::string& name, const std::vector<Vertex>& data,
                       const std::vector<uint32_t>& indices);
  static void InitQuad3D(const std::string& name);

    private:
        std::vector<std::string> entities_;
};

}  // namespace musashi

#endif
