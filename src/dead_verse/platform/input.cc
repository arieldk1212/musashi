#include "global.h"
#include "input.h"
#include "platform.h"

namespace musashi {

bool InputSystem::IsKeyPressed(KeyCode key_code) {
  return keys_[key_code];
}

bool InputSystem::IsMouseButtonPressed(KeyCode key_code) {
  return keys_[key_code];
}

glm::vec2 InputSystem::GetMousePosition() {
  double x{0.0};
  double y{0.0};
  glfwGetCursorPos(kPlatform->window->GetHandler(), &x, &y);
  return glm::vec2{static_cast<float>(x), static_cast<float>(y)};
}

// Input::Input(Camera& camera)
//     : camera_(camera) {}

// void Input::Init(GLFWwindow* window) {
//   glfwSetWindowUserPointer(window, this);
//   SetInputMode(window, kDefaultInputMode);
//   glfwSetCursorPosCallback(window, MouseCallbackWrapper);
//   glfwSetScrollCallback(window, ScrollCallbackWrapper);
//   kGlobal.logger->Trace("INPUT INITIALIZED");
// }

// void Input::ProcessInput(GLFWwindow* window, float delta_time) {
//   if (KeyPressed(window, KeyCode::kEsc)) {
//     glfwSetWindowShouldClose(window, static_cast<int>(true));
//   }
// }

// void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
//   xpos = static_cast<float>(xpos);
//   ypos = static_cast<float>(ypos);

//   if (first_mouse_) {
//     camera_.mouse_offset.last_x = xpos;
//     camera_.mouse_offset.last_y = ypos;
//     first_mouse_ = false;
//   }

//   float xoffset = xpos - camera_.mouse_offset.last_x;
//   float yoffset = camera_.mouse_offset.last_y -
//                   ypos;  // reversed, y-coordinates range from bottom to top

//   camera_.mouse_offset.last_x = xpos;
//   camera_.mouse_offset.last_y = ypos;

//   CameraProcessMouseMovement(xoffset, yoffset);
// }

// bool Input::KeyPressed(GLFWwindow* window, KeyCode key_code) {
//   auto state = glfwGetKey(window, static_cast<int>(key_code));
//   return state == GLFW_PRESS || state == GLFW_REPEAT;
// }

// bool Input::MouseButtonPressed(GLFWwindow* window, KeyCode button) {
//   auto state = glfwGetKey(window, static_cast<int>(button));
//   return state == GLFW_PRESS;
// }

// void Input::CameraProcessMouseMovement(float x_offset, float y_offset,
//                                        GLboolean constrain_pitch) {
//   x_offset *= camera_.settings.mouse_sensitivity;
//   y_offset *= camera_.settings.mouse_sensitivity;

//   camera_.settings.yaw += x_offset;
//   camera_.settings.pitch += y_offset;

//   if (constrain_pitch) {
//     camera_.settings.pitch = std::clamp(camera_.settings.pitch,
//     -89.0f, 89.0f);
//   }

//   camera_.Update();
// }

// void Input::CameraProcessMouseScroll(float y_offset) {
//   camera_.settings.zoom -= y_offset;
//   camera_.settings.zoom = std::clamp(camera_.settings.zoom, 1.0f, 45.0f);
// }

// void Input::MouseCallbackWrapper(GLFWwindow* window, double xpos, double
// ypos) {
//   auto* instance = static_cast<Input*>(glfwGetWindowUserPointer(window));
//   if (instance != nullptr) {
//     instance->MouseCallback(window, xpos, ypos);
//   } else {
//     kGlobal.logger->Error("INPUT INSTANCE NULLPTR");
//   }
// }

// void Input::ScrollCallbackWrapper(GLFWwindow* window, double xoffset,
//                                   double yoffset) {
//   auto* instance = static_cast<Input*>(glfwGetWindowUserPointer(window));
//   if (instance != nullptr) {
//     instance->CameraProcessMouseScroll(static_cast<float>(yoffset));
//   } else {
//     kGlobal.logger->Error("INPUT INSTANCE NULLPTR");
//   }
// }

}  // namespace musashi
