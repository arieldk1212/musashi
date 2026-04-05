#include "global.h"
#include "input.h"

#include <algorithm>

#include "util/log.h"

namespace musashi {

Input::Input()
    : camera_(glm::vec3(0.0f, 0.0f, kCameraZStart)) {
  kGlobal.logger->Trace("INPUT CREATED");
}

void Input::ProcessInput(GLFWwindow* window) {
  if (KeyPressed(window, KeyCode::kEsc)) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Input::CallbackWrapper(std::function<void()> callback) {}

bool Input::KeyPressed(GLFWwindow* window, KeyCode key_code) {
  auto state = glfwGetKey(window, static_cast<int>(key_code));
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::MouseButtonPressed(GLFWwindow* window, KeyCode button) {
  auto state = glfwGetKey(window, static_cast<int>(button));
  return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition(GLFWwindow* window) {
  double x{0.0};
  double y{0.0};
  glfwGetCursorPos(window, &x, &y);
  return {static_cast<float>(x), static_cast<float>(y)};
}

void Input::CameraProcessKeyboard(CameraMovement direction, float delta_time) {
  float velocity = camera_.movement_speed * delta_time;
  switch (direction) {
    case CameraMovement::kForward:
      camera_.position += velocity * camera_.front;
      break;
    case CameraMovement::kBackward:
      camera_.position -= velocity * camera_.front;
      break;
    case CameraMovement::kLeft:
      camera_.position -= velocity * camera_.right;
      break;
    case CameraMovement::kRight:
      camera_.position += velocity * camera_.right;
      break;
  }
  // FPS
  camera_.position.y = 0.0f;
}

void Input::CameraProcessMouseMovement(float x_offset, float y_offset,
                                       GLboolean constrain_pitch) {
  x_offset *= camera_.mouse_sensitivity;
  y_offset *= camera_.mouse_sensitivity;

  camera_.yaw += x_offset;
  camera_.pitch += y_offset;

  if (constrain_pitch) {
    camera_.pitch = std::clamp(camera_.pitch, -89.0f, 89.0f);
  }

  camera_.UpdateCameraVectors();
}

void Input::CameraProcessMouseScroll(float y_offset) {
  camera_.zoom -= y_offset;
  camera_.zoom = std::clamp(camera_.zoom, 1.0f, 45.0f);
}

}  // namespace musashi
