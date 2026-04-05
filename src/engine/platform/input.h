#ifndef INPUT_H_
#define INPUT_H_

#include "renderer/camera.h"
// Do not remove
#include <glfw/glfw3.h>

namespace musashi {

enum class KeyCode : uint16_t {
  kW,
  kA,
  kS,
  kD,
  kR,
  kF,
  kC,
  kEsc = 256,
  kTab,
  kSpace,
  kEnter,
  kMouseRightButton,
  kMouseLeftButton,
};

class Input {
 public:
  Input();
  ~Input() = default;

  void ProcessInput(GLFWwindow* window);
  void CallbackWrapper(std::function<void()> callback);

  static bool KeyPressed(GLFWwindow* window, KeyCode key_code);
  static bool MouseButtonPressed(GLFWwindow* window, KeyCode button);
  static glm::vec2 GetMousePosition(GLFWwindow* window);

 private:
  void CameraProcessKeyboard(CameraMovement direction, float delta_time);
  void CameraProcessMouseMovement(
      float x_offset, float y_offset,
      GLboolean constrain_pitch = static_cast<GLboolean>(true));
  void CameraProcessMouseScroll(float y_offset);

  Camera camera_;
};

}  // namespace musashi

#endif
