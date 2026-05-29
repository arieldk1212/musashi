#include "renderer/resource_manager.h"
#include "space/game/game.h"

int main() {
  static constexpr musashi::GameSpecification kSpecs = {
      .game_name = "Space",
      .window_specs.width = 1700,
      .window_specs.height = 1100,
      .window_specs.is_resizeable = true};

  // Engine Dependencies
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::Platform platform(logger, kSpecs.window_specs);
  musashi::ComponentManager ec(logger);
  musashi::ResourceManager resource_manager(logger);
  musashi::Renderer renderer(logger, platform, ec, resource_manager);
  musashi::Physics physics(logger);

  // Game
  musashi::GameDependencies dependencies(logger, renderer, platform, ec,
                                         physics);
  musashi::Game game(dependencies, resource_manager, kSpecs);

  // Entrypoint
  logger.Trace("GAME STARTING..");
  game.Run();

  // Shutdown
  renderer.ShutDown();

  return 0;
}
