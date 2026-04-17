#include "global.h"
#include "input.h"
#include "platform.h"

#include "GLFW/glfw3.h"

namespace musashi {

void InputSystem::Init(Mode mode) {
  SetCursorMode(mode);

  glfwSetWindowUserPointer(kPlatform->window->GetHandler(), this);

  auto wrapper_input = [](GLFWwindow* window, int key, int code, int action,
                          int mods) {
    static_cast<Platform*>(glfwGetWindowUserPointer(window))
        ->input_system.InputCallback(window, key, code, action, mods);
  };
  glfwSetKeyCallback(kPlatform->window->GetHandler(), wrapper_input);
}

void InputSystem::InputCallback(GLFWwindow* window, int key, int code,
                                int action, int mods) {
  auto key_code = static_cast<KeyCode>(key);

  if (key_code == KeyCode::kEscape && action == GLFW_PRESS) {
    kPlatform->window->SetShouldClose();
    return;
  }

  switch (action) {
    case GLFW_REPEAT:
      break;
    case GLFW_PRESS:
      SetKey(static_cast<KeyCode>(key));
      break;
    case GLFW_RELEASE:
      UnsetKey(static_cast<KeyCode>(key));
      break;
    default:
      return;
  };
}

bool InputSystem::KeyPressed(KeyCode key_code) {
  auto state =
      glfwGetKey(kPlatform->window->GetHandler(), static_cast<int>(key_code));
  return state == GLFW_PRESS;
}

bool InputSystem::MouseButtonPressed(KeyCode key_code) {
  auto state =
      glfwGetKey(kPlatform->window->GetHandler(), static_cast<int>(key_code));
  return state == GLFW_PRESS;
}

bool InputSystem::IsKeyPressed(KeyCode key_code) {
  return keys_[key_code];
}

bool InputSystem::IsMouseButtonPressed(KeyCode key_code) {
  return keys_[key_code];
}

void InputSystem::SetCursorMode(Mode mode) {
  cursor_mode_ = mode;
  glfwSetInputMode(kPlatform->window->GetHandler(), GLFW_CURSOR,
                   static_cast<int>(mode));
}

glm::vec2 InputSystem::GetMousePosition() {
  double x{0.0};
  double y{0.0};
  glfwGetCursorPos(kPlatform->window->GetHandler(), &x, &y);
  return glm::vec2{static_cast<float>(x), static_cast<float>(y)};
}

// bool Input::KeyPressed(GLFWwindow* window, KeyCode key_code) {
//   auto state = glfwGetKey(window, static_cast<int>(key_code));
//   return state == GLFW_PRESS || state == GLFW_REPEAT;
// }

// bool Input::MouseButtonPressed(GLFWwindow* window, KeyCode button) {
//   auto state = glfwGetKey(window, static_cast<int>(button));
//   return state == GLFW_PRESS;
// }

}  // namespace musashi
