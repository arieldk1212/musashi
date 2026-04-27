#ifndef GAME_H_
#define GAME_H_

#include "state.h"
#include "world.h"

#include <string>

#include "entity/component_manager.h"
#include "platform/platform.h"
#include "platform/window.h"
#include "renderer/renderer.h"
#include "util/log.h"
#include "util/time.h"

namespace musashi {

struct GameSpecification {
  std::string game_name = "Dead Verse";
  WindowSpecification window_specs;
};

struct GameDependencies {
  GameDependencies(Logger& logger, Renderer& renderer, Platform& platform,
                   ComponentManager& ec)
      : logger(logger),
        platform(platform),
        renderer(renderer),
        ec(ec) {}
  Logger& logger;
  Platform& platform;
  Renderer& renderer;
  ComponentManager& ec;
};

class Game {
 public:
  explicit Game(GameDependencies& dependencies,
                const GameSpecification& specs = GameSpecification());
  ~Game() noexcept;

  void Init();
  void Run();
  void Stop() { running_ = false; }
  void Update(float ts = 0);

 private:
  Time time_;
  bool running_{false};
  GameDependencies* dependencies_;
  GameSpecification specifications_;
  std::shared_ptr<World> world_;
  std::unique_ptr<State> state_;
};

}  // namespace musashi

#endif
