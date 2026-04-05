#ifndef INPUT_H_
#define INPUT_H_

// clang-format off
#include "renderer/camera.h"

#include <glfw/glfw3.h>
//clang-format on

namespace musashi {

class Input {
 public:
  Input();
  ~Input() = default;

  void ProcessInput(GLFWwindow* window);

  void CallbackWrapper(std::function<void()> callback);

 private:
  void ProcessKeyboard();
  void ProcessMouseMovement();
  void ProcessMouseScroll();

  std::unique_ptr<Camera> camera_;
};

}  // namespace musashi

#endif
