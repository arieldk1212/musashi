#include "simulator/musashi/musashi.h"
#include "simulator/renderer/resource_manager.h"
#include "simulator/ui/ui.h"

int main() {
  static const musashi::SimulatorSpecifications kSpecs = {
      .game_name = "Musashi Simulator",
      .window_specs = {.is_resizeable = true, .width = 1700, .height = 1100}};

  // Engine Dependencies
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::Platform platform(logger, kSpecs.window_specs);
  musashi::ComponentManager ec(logger);
  musashi::ResourceManager resource_manager(logger);
  musashi::Renderer renderer(logger, platform, ec, resource_manager);
  musashi::Physics physics(logger);

  // Simulator
  musashi::SimulatorDependencies dependencies(logger, renderer, platform, ec,
                                              physics);
  musashi::Musashi musashi(dependencies, resource_manager, kSpecs);
  musashi::Ui ui(platform.window);

  // Entrypoint
  logger.Trace("GAME STARTING..");
  musashi.Run();

  // Shutdown
  renderer.ShutDown();

  return 0;
}
