#include "platform.h"

#include "util/camera.h"

namespace musashi {

Platform::Platform(Logger& logger, const WindowSpecification& specifications)
    : logger(&logger),
      window(std::make_shared<Window>(logger, specifications)),
      input_system(window),
      camera(window) {}

void Platform::Init() {
  window->Create();
  glfwSetWindowUserPointer(window->GetHandler(), this);
  input_system.Init();
  camera.Init();
}

void Platform::Clear() {
  input_system.Clear();
}

void Platform::Destroy() {
  if (window) {
    window->Destroy();
  }
  window.reset();
}

void Platform::Update(float ts) {}

}  // namespace musashi
