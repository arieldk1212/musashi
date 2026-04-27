#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "input.h"

#include "util/camera.h"
#include "util/log.h"

namespace musashi {

struct Platform {
  explicit Platform(Logger& logger, const WindowSpecification& specifications);

  void Init();
  void Clear();
  void Destroy();
  void Update(float ts);

  Logger* logger;
  std::shared_ptr<Window> window;
  InputSystem input_system;
  PrespectiveCameraController camera;
};

}  // namespace musashi

#endif
