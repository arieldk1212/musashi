#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "input.h"
#include "window.h"

#include <memory>
#include "util/camera.h"

namespace musashi {

struct Platform {
  explicit Platform(const WindowSpecification& specifications);

  void Init();
  void Destroy() const;
  void Update(float ts);

  std::shared_ptr<Window> window;
  PrespectiveCameraController camera;
  InputSystem input_system;
};

}  // namespace musashi

#endif
