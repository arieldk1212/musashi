#include "platform.h"

#include "platform/window.h"

namespace musashi {

Platform::Platform(const WindowSpecification& specifications)
    : window(std::make_shared<Window>(specifications)),
      camera(glm::vec3(0.0f, 0.0f, kCameraZStart)),
      input(camera, specifications.width, specifications.height) {}

void Platform::Init() {
  window->Create();
  input.Init(window->GetHandler());
}

void Platform::Destroy() const {
  window->Destory();
}

}  // namespace musashi
