#include "platform.h"

namespace musashi {

Platform::Platform(const WindowSpecification& specifications)
    : window(std::make_shared<Window>(specifications)) {}

void Platform::Init() {
  window->Create();
  input_system.Init();
}

void Platform::Destroy() const {
  window->Destory();
}

}  // namespace musashi
