#include "dead_verse/game/game.h"
#include "renderer/resource_manager.h"

int main() {
  musashi::GameSpecification specs{.game_name = "Dead Verse",
                                   .window_specs.width = 1000,
                                   .window_specs.height = 800,
                                   .window_specs.is_resizeable = true};

  // Engine Dependencies
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::Platform platform(logger, specs.window_specs);
  musashi::ComponentManager ec(logger);
  musashi::ResourceManager resource_manager(logger);
  musashi::Renderer renderer(logger, platform, ec, resource_manager);

  // Game
  musashi::GameDependencies dependencies(logger, renderer, platform, ec);
  musashi::Game game(dependencies, specs);

  // Entrypoint
  logger.Trace("GAME STARTING..");
  game.Run();

  // Shutdown
  renderer.ShutDown();

  return 0;
}
