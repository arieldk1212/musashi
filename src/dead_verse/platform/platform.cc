#include "platform.h"

#include "platform/input.h"

namespace musashi {

Platform::Platform(const WindowSpecification& specifications)
    : window(std::make_shared<Window>(specifications)) {}

void Platform::Init() {
  window->Create();
  input_system.Init();
  camera.Init();
}

void Platform::Clear() {
  input_system.Clear();
}

void Platform::Destroy() const {
  window->Destroy();
}

void Platform::Update(float ts) {}

}  // namespace musashi
