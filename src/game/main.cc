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

  musashi::kGlobal.application = &application;

  application.PushLayer<dead_verse::AppLayer>();
  musashi::kGlobal.application->Run();

  return 0;
}