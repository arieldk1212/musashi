#include "dead_verse/game/game.h"
#include "dead_verse/ui/ui.h"
#include "renderer/resource_manager.h"

int main() {
  static constexpr musashi::GameSpecification kSpecs = {
      .game_name = "Dead Verse",
      .window_specs = {.is_resizeable = true, .width = 1700, .height = 1100}};

  // Engine Dependencies
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::Platform platform(logger, kSpecs.window_specs);
  musashi::Ui ui(platform.window);
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
