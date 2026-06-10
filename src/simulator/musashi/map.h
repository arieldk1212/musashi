#ifndef MAP_H_
#define MAP_H_

#include "game/world.h"
namespace musashi {

struct Map {
  void Init();  // NOTE: Init textures for the map
  void DrawMap(World* world);
};

}  // namespace musashi

#endif
