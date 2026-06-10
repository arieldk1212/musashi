#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "input.h"

#include "util/camera.h"
#include "util/log.h"

namespace musashi {

struct Platform {
  Logger* logger;
  std::shared_ptr<Window> window;
  InputSystem input_system;
  PrespectiveCameraController camera;

  explicit Platform(Logger& logger, const WindowSpecification& specifications);
  ~Platform() = default;

  Platform(const Platform&) = delete;
  Platform& operator=(const Platform&) = delete;
  Platform(Platform&&) = delete;
  Platform& operator=(Platform&&) = delete;

  void Init();
  void Clear();
  void Destroy();
  void Update(float ts);
};

}  // namespace musashi

#endif
