#include "global.h"
#include "input.h"

#include <algorithm>

#include "util/camera.h"
#include "util/log.h"

namespace musashi {

Input::Input(Camera& camera, uint32_t width, uint32_t height)
    : camera_(camera),
      last_x_(static_cast<float>(width / 2)),
      last_y_(static_cast<float>(height / 2)) {}

void Input::Init(GLFWwindow* window) {
  glfwSetWindowUserPointer(window, this);
  SetInputMode(window, kDefaultInputMode);
  glfwSetCursorPosCallback(window, MouseCallbackWrapper);
  glfwSetScrollCallback(window, ScrollCallbackWrapper);
  kGlobal.logger->Trace("INPUT INITIALIZED");
}

void Input::ProcessInput(GLFWwindow* window, float delta_time) {
  if (KeyPressed(window, KeyCode::kEsc)) {
    glfwSetWindowShouldClose(window, static_cast<int>(true));
    kGlobal.logger->Debug("EXISTING..");
  }

  if (KeyPressed(window, KeyCode::kW)) {
    CameraProcessKeyboard(CameraMovement::kForward, delta_time);
    kGlobal.logger->Debug("Key Press: W");
  }
  if (KeyPressed(window, KeyCode::kA)) {
    CameraProcessKeyboard(CameraMovement::kLeft, delta_time);
    kGlobal.logger->Debug("Key Press: A");
  }
  if (KeyPressed(window, KeyCode::kS)) {
    CameraProcessKeyboard(CameraMovement::kBackward, delta_time);
    kGlobal.logger->Debug("Key Press: S");
  }
  if (KeyPressed(window, KeyCode::kD)) {
    CameraProcessKeyboard(CameraMovement::kRight, delta_time);
    kGlobal.logger->Debug("Key Press: D");
  }
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
  xpos = static_cast<float>(xpos);
  ypos = static_cast<float>(ypos);

  if (first_mouse_) {
    last_x_ = xpos;
    last_y_ = ypos;
    first_mouse_ = false;
  }

  float xoffset = xpos - last_x_;
  float yoffset =
      last_y_ - ypos;  // reversed, y-coordinates range from bottom to top

  last_x_ = xpos;
  last_y_ = ypos;

  CameraProcessMouseMovement(xoffset, yoffset);
}

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

  camera_.Update();
}

void Input::CameraProcessMouseScroll(float y_offset) {
  camera_.zoom -= y_offset;
  camera_.zoom = std::clamp(camera_.zoom, 1.0f, 45.0f);
}

void Input::MouseCallbackWrapper(GLFWwindow* window, double xpos, double ypos) {
  auto* instance = static_cast<Input*>(glfwGetWindowUserPointer(window));
  if (instance != nullptr) {
    instance->MouseCallback(window, xpos, ypos);
  } else {
    kGlobal.logger->Error("INPUT INSTANCE NULLPTR");
  }
}

void Input::ScrollCallbackWrapper(GLFWwindow* window, double xoffset,
                                  double yoffset) {
  auto* instance = static_cast<Input*>(glfwGetWindowUserPointer(window));
  if (instance != nullptr) {
    instance->CameraProcessMouseScroll(static_cast<float>(yoffset));
  } else {
    kGlobal.logger->Error("INPUT INSTANCE NULLPTR");
  }
}

}  // namespace musashi
