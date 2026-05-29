#ifndef WORLD_H_
#define WORLD_H_

#include "entity/component_manager.h"
#include "renderer/resource_manager.h"
#include "util/log.h"

namespace musashi {

// TODO: Implement State Machine Here
class World {
 public:
  World(Logger* logger, ComponentManager* ec,
        ResourceManager* resource_manager);

  void Init();
  void InitTiles();

 private:
  Logger* logger_;
  ComponentManager* ec_;
  ResourceManager* resource_manager_;
};

}  // namespace musashi

#endif
