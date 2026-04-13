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

  Input input;
  Camera camera;
  std::shared_ptr<Window> window;
};

}  // namespace musashi

#endif
