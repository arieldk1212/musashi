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
  void Clear();
  void Destroy() const;
  void Update(float ts);

  InputSystem input_system;
  std::shared_ptr<Window> window;
  PrespectiveCameraController camera;
};

}  // namespace musashi

#endif
