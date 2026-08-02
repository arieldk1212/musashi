#ifndef MUSASHI_H_
#define MUSASHI_H_

#include "physics.h"
#include "state.h"

#include <string>

#include "entity/component_manager.h"
#include "platform/platform.h"
#include "platform/window.h"
#include "renderer/renderer.h"
#include "util/log.h"
#include "util/time.h"

namespace musashi {

struct SimulatorSpecifications {
  std::string game_name = "Simulator";
  WindowSpecification window_specs;
};

struct SimulatorDependencies {
  SimulatorDependencies(Logger& logger, Renderer& renderer, Platform& platform,
                        ComponentManager& ec, Physics& physics)
      : logger(logger),
        platform(platform),
        renderer(renderer),
        ec(ec),
        physics(physics) {}
  Logger& logger;
  Platform& platform;
  Renderer& renderer;
  ComponentManager& ec;
  Physics& physics;
};

class Musashi {
 public:
  explicit Musashi(
      SimulatorDependencies& dependencies, ResourceManager& resource_manager,
      const SimulatorSpecifications& specs = SimulatorSpecifications());
  ~Musashi() noexcept;

  void Init();
  void Run();
  void Stop() { running_ = false; }
  void Update(float ts = 0);

 private:
  Time time_;
  bool running_{false};
  SimulatorDependencies* dependencies_;
  ResourceManager* resource_manager_;
  SimulatorSpecifications specifications_;
  std::shared_ptr<World> world_;
  std::unique_ptr<State> state_;
};

}  // namespace musashi

#endif
