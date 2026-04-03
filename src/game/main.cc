#include "core/log.h"
#include "engine/application.h"
#include "engine/global.h"
#include "layers/app_layer.h"

musashi::Global musashi::kGlobal{};

int main() {
  musashi::ApplicationSpecification specs;
  specs.application_name = "Dead Verse";
  specs.window_specs.width = 1000;
  specs.window_specs.height = 800;

  musashi::Application application(specs);
  musashi::Logger logger(musashi::kLogBufferSize);

  musashi::kGlobal.application = &application;
  musashi::kGlobal.logger = &logger;

  application.PushLayer<dead_verse::AppLayer>();
  musashi::kGlobal.application->Run();

  return 0;
}
