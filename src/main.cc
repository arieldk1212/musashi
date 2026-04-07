#include "dead_verse/game.h"
#include "dead_verse/global.h"
#include "dead_verse/platform/input.h"
#include "dead_verse/renderer/renderer.h"
#include "dead_verse/states/game_state.h"
#include "dead_verse/util/log.h"

musashi::Global musashi::kGlobal;

int main() {
  musashi::GameSpecification specs;
  specs.game_name = "Dead Verse";
  specs.window_specs.width = 1000;
  specs.window_specs.height = 800;

  // Setup - Change this.
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::kGlobal.logger = &logger;

  musashi::Game game(specs);
  musashi::kGlobal.game = &game;

  musashi::GameState state;
  musashi::kGlobal.state = &state;

  musashi::Input input(specs.window_specs.width, specs.window_specs.height);
  musashi::kGlobal.input = &input;

  musashi::Renderer renderer;
  musashi::kGlobal.renderer = &renderer;

  // Main Logic
  musashi::kGlobal.logger->Trace("LOGGING INITIALIZED");  // Change this
  musashi::kGlobal.game->Run();

  // Cleanup
  musashi::Global::Cleanup(musashi::kGlobal);

  return 0;
}
