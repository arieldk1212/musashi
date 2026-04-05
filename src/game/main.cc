#include "engine/application.h"
#include "engine/global.h"
#include "engine/platform/input.h"
#include "engine/renderer/renderer.h"
#include "engine/util/log.h"

musashi::Global musashi::kGlobal;

int main() {
  musashi::ApplicationSpecification specs;
  specs.application_name = "Dead Verse";
  specs.window_specs.width = 1000;
  specs.window_specs.height = 800;

  // Setup - Change this.
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::kGlobal.logger = &logger;

  musashi::Input input;
  musashi::kGlobal.input = &input;

  musashi::Application application(specs);
  musashi::kGlobal.application = &application;

  musashi::Renderer renderer;
  musashi::kGlobal.renderer = &renderer;

  // Main Logic
  musashi::kGlobal.logger->Trace("LOGGING INITIALIZED");  // Change this
  musashi::kGlobal.application->Run();

  // Cleanup
  musashi::Global::Cleanup(musashi::kGlobal);

  return 0;
}
