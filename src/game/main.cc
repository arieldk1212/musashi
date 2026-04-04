#include "engine/application.h"
#include "engine/core/log.h"
#include "engine/global.h"
#include "layers/app_layer.h"

musashi::Global musashi::kGlobal{};

int main() {
  musashi::ApplicationSpecification specs;
  specs.application_name = "Dead Verse";
  specs.window_specs.width = 1000;
  specs.window_specs.height = 800;

  // Setup
  musashi::Logger logger(musashi::kLogBufferSize);
  musashi::kGlobal.logger = &logger;

  musashi::Application application(specs);
  musashi::kGlobal.application = &application;

  // Main Logic
  application.PushLayer<dead_verse::AppLayer>();
  musashi::kGlobal.logger->Trace("LOGGING INITIALIZED");
  musashi::kGlobal.application->Run();

  // Cleanup
  musashi::kGlobal.application = nullptr;
  musashi::kGlobal.logger = nullptr;

  return 0;
}
