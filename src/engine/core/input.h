#ifndef INPUT_H_
#define INPUT_H_

#include <cstdint>

#include "core/window.h"

namespace musashi {

class Input {
 public:
  enum class InputMode : uint8_t { kNormal, kHidden, kDisabled, kCaptured };
  Input();

  static void SetInputMode(Window* window, InputMode mode) {
    switch (mode) {
      case InputMode::kNormal:
        glfwSetInputMode(window->GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;
      case InputMode::kDisabled:
        glfwSetInputMode(window->GetHandle(), GLFW_CURSOR,
                         GLFW_CURSOR_DISABLED);
        break;
      default:
    }
  }

 private:
};

}  // namespace musashi

#endif