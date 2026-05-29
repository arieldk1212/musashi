#include "world.h"

namespace musashi {

World::World(Logger* logger, ComponentManager* ec,
             ResourceManager* resource_manager)
    : logger_(logger),
      ec_(ec),
      resource_manager_(resource_manager) {
  Init();
}

void World::InitTiles() {}

void World::Init() {
  InitTiles();
}

}  // namespace musashi
