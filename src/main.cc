#include "dead_verse/game/game.h"

int main() {
  musashi::GameSpecification specs;
  specs.game_name = "Dead Verse";
  specs.window_specs.width = 1000;
  specs.window_specs.height = 800;
  specs.window_specs.is_resizeable = true;

  // Engine Dependencies
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::Platform platform(logger, specs.window_specs);
  musashi::ComponentManager ec(logger);
  musashi::Renderer renderer(logger, platform, ec);

  // Game
  musashi::GameDependencies dependencies(logger, renderer, platform, ec);
  musashi::Game game(dependencies, specs);

  // Entrypoint
  logger.Trace("GAME STARTING..");
  game.Run();

  return 0;
}
