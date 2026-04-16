#ifndef INPUT_H_
#define INPUT_H_

#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"
#include "unordered_map"

namespace musashi {

enum class Mode : unsigned int {
  kCursorDisabled = GLFW_CURSOR_DISABLED,
  kCursorNormal = GLFW_CURSOR_NORMAL,
  kCursorHidden = GLFW_CURSOR_HIDDEN,
  kCursorCaptured = GLFW_CURSOR_CAPTURED
};

enum class KeyCode : uint16_t {
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
  kMouseRightButton = 1,
  kMouseMiddleButton = 2
};

class InputSystem {
 public:
  InputSystem() = default;

  void Init();

  bool IsKeyPressed(KeyCode key_code);
  bool IsMouseButtonPressed(KeyCode key_code);
  void ClearKeys() { keys_.clear(); }

  void SetKey(KeyCode key_code) { keys_[key_code] = true; }
  void SetCursorMode(Mode mode) { cursor_mode_ = mode; }

  static glm::vec2 GetMousePosition();

 private:
  Mode cursor_mode_{Mode::kCursorHidden};
  std::unordered_map<KeyCode, bool> keys_;
};

// class Input {
//  public:
//   explicit Input(Camera& camera);
//   ~Input() = default;

//   static constexpr InputMode kDefaultInputMode{InputMode::kCursorHidden};

//   void Init(GLFWwindow* window);
//   void ProcessInput(GLFWwindow* window, float delta_time);
//   void MouseCallback(GLFWwindow* window, double xpos, double ypos);

//   bool KeyPressed(GLFWwindow* window, KeyCode key_code);
//   bool MouseButtonPressed(GLFWwindow* window, KeyCode button);
//   glm::vec2 GetMousePosition(GLFWwindow* window);
//   static void SetInputMode(GLFWwindow* window, InputMode mode) {
//     glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
//   }

//  private:
//   void CameraProcessKeyboard(CameraMovement direction, float delta_time);
//   void CameraProcessMouseMovement(
//       float x_offset, float y_offset,
//       GLboolean constrain_pitch = static_cast<GLboolean>(true));
//   void CameraProcessMouseScroll(float y_offset);

//   static void MouseCallbackWrapper(GLFWwindow* window, double xpos,
//                                    double ypos);
//   static void ScrollCallbackWrapper(GLFWwindow* window, double xoffset,
//                                     double yoffset);

//   bool first_mouse_{true};
// };

}  // namespace musashi

#endif
