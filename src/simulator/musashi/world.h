#ifndef WORLD_H_
#define WORLD_H_

#include "player.h"

#include <memory>
#include <string>

#include "entity/component_manager.h"
#include "renderer/resource_manager.h"
#include "util/log.h"

namespace musashi {

class World {
 public:
  World(Logger* logger, ComponentManager* ec,
        ResourceManager* resource_manager);

  void Init();
  void InitLevel();
  void InitTiles();
  void InitPlayer(const std::string& name);

 private:
  Logger* logger_;
  ComponentManager* ec_;
  std::unique_ptr<Player> player_;
  ResourceManager* resource_manager_;
};

}  // namespace musashi

#endif
