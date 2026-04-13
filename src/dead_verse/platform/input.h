#ifndef INPUT_H_
#define INPUT_H_

#include "window.h"

#include "util/camera.h"
// Do not remove

#include <GLFW/glfw3.h>

namespace musashi {

struct Command {
  virtual ~Command() = 0;
  virtual void Execute() = 0;
};

struct JumpCommand : public Command {};

enum class InputMode : unsigned int {
  // Mapped to glfw
  kCursorDisabled = GLFW_CURSOR_DISABLED,
  kCursorNormal = GLFW_CURSOR_NORMAL,
  kCursorHidden = GLFW_CURSOR_HIDDEN,
  kCursorCaptured = GLFW_CURSOR_CAPTURED
};

enum class KeyCode : uint16_t {
  // Mapped to glfw
  kW = 87,
  kA = 65,
  kS = 83,
  kD = 68,
  kR = 82,
  kF = 70,
  kC = 67,
  kEsc = 256,
  kTab = 258,
  kSpace = 32,
  kEnter = 257,
  kMouseLeftButton = 0,
  kMouseRightButton = 1
};

class Input {
 public:
  Input(uint32_t width, uint32_t height);
  ~Input() = default;

  static constexpr InputMode kDefaultInputMode{InputMode::kCursorHidden};

  void Init(GLFWwindow* window);
  void ProcessInput(GLFWwindow* window, float delta_time);
  void MouseCallback(GLFWwindow* window, double xpos, double ypos);

  bool KeyPressed(GLFWwindow* window, KeyCode key_code);
  bool MouseButtonPressed(GLFWwindow* window, KeyCode button);
  glm::vec2 GetMousePosition(GLFWwindow* window);
  static void SetInputMode(GLFWwindow* window, InputMode mode) {
    glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
  }

 private:
  void CameraProcessKeyboard(CameraMovement direction, float delta_time);
  void CameraProcessMouseMovement(
      float x_offset, float y_offset,
      GLboolean constrain_pitch = static_cast<GLboolean>(true));
  void CameraProcessMouseScroll(float y_offset);

  static void FramebufferSizeCallback(GLFWwindow* window, int width,
                                      int height);
  static void MouseCallbackWrapper(GLFWwindow* window, double xpos,
                                   double ypos);
  static void ScrollCallbackWrapper(GLFWwindow* window, double xoffset,
                                    double yoffset);

  float last_x_;
  float last_y_;
  Camera camera_;
  bool first_mouse_{true};
};

}  // namespace musashi

#endif
