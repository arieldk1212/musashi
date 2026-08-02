#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <memory>

#include "musashi/world.h"
#include "util/log.h"

namespace musashi {

class Physics {
 public:
  explicit Physics(Logger& logger)
      : logger_(&logger) {}
  void Update(std::shared_ptr<World> world) {}

 private:
  Logger* logger_;
};

}  // namespace musashi

#endif
