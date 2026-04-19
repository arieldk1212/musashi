#include "camera.h"
#include "global.h"

#include <algorithm>

#include "GLFW/glfw3.h"
#include "platform/input.h"
#include "platform/platform.h"
#include "util/log.h"

namespace musashi {

PrespectiveCamera::PrespectiveCamera(const glm::vec3& position)
    : position(position) {}

void PrespectiveCamera::Update() {
  glm::vec3 front;
  front.x = cos(glm::radians(settings.yaw)) * cos(glm::radians(settings.pitch));
  front.y = sin(glm::radians(settings.pitch));
  front.z = sin(glm::radians(settings.yaw)) * cos(glm::radians(settings.pitch));
  vectors.front = glm::normalize(front);

  vectors.right = glm::normalize(glm::cross(vectors.front, vectors.world_up));
  vectors.up = glm::normalize(glm::cross(vectors.right, vectors.front));

  view_matrix = CalculateNewViewMatrix();

  projection_matrix =
      glm::perspective(glm::radians(settings.zoom),
                       kPlatform->window->GetWindowResolutionWidth() /
                           kPlatform->window->GetWindowResolutionHeight(),
                       0.1f, 100.0f);

  view_projection_matrix = projection_matrix * view_matrix;
}

PrespectiveCameraController::PrespectiveCameraController(
    const glm::vec3& position)
    : camera(position) {}

void PrespectiveCameraController::Init() {
  auto wrapper_mouse = [](GLFWwindow* window, double x, double y) {
    static_cast<Platform*>(glfwGetWindowUserPointer(window))
        ->camera.CallbackMouse(x, y);
  };

  auto wrapper_scroll = [](GLFWwindow* window, double x, double y) {
    static_cast<Platform*>(glfwGetWindowUserPointer(window))
        ->camera.CallbackScroll(static_cast<float>(y));
  };

  glfwSetCursorPosCallback(kPlatform->window->GetHandler(), wrapper_mouse);
  glfwSetScrollCallback(kPlatform->window->GetHandler(), wrapper_scroll);
}

void PrespectiveCameraController::Update(float delta_time) {
  auto& input_system = kPlatform->input_system;

  if (input_system.IsKeyPressed(KeyCode::kW)) {
    CameraProcessKeyboard(CameraMovement::kForward, delta_time);
  }
  if (input_system.IsKeyPressed(KeyCode::kA)) {
    CameraProcessKeyboard(CameraMovement::kLeft, delta_time);
  }
  if (input_system.IsKeyPressed(KeyCode::kS)) {
    CameraProcessKeyboard(CameraMovement::kBackward, delta_time);
  }
  if (input_system.IsKeyPressed(KeyCode::kD)) {
    CameraProcessKeyboard(CameraMovement::kRight, delta_time);
  }
}

void PrespectiveCameraController::CameraProcessKeyboard(
    CameraMovement direction, float delta_time) {
  float velocity = camera.settings.movement_speed * delta_time;
  switch (direction) {
    case CameraMovement::kForward:
      camera.position += velocity * camera.vectors.front;
      break;
    case CameraMovement::kBackward:
      camera.position -= velocity * camera.vectors.front;
      break;
    case CameraMovement::kLeft:
      camera.position -= velocity * camera.vectors.right;
      break;
    case CameraMovement::kRight:
      camera.position += velocity * camera.vectors.right;
      break;
  }
  camera.position.y = 0.0f;  // FPS

  camera.Update();
}

void PrespectiveCameraController::CallbackMouse(double x_pos, double y_pos) {
  auto x_posf = static_cast<float>(x_pos);
  auto y_posf = static_cast<float>(y_pos);

  if (camera.settings.first_mouse) {
    mouse_offset.last_x = x_posf;
    mouse_offset.last_y = y_posf;
    camera.settings.first_mouse = false;
  }

  float x_offset = x_posf - mouse_offset.last_x;
  float y_offset = mouse_offset.last_y - y_posf;

  mouse_offset.last_x = x_posf;
  mouse_offset.last_y = y_posf;

  x_offset *= camera.settings.mouse_sensitivity;
  y_offset *= camera.settings.mouse_sensitivity;

  camera.settings.yaw += x_offset;
  camera.settings.pitch += y_offset;

  static float kUpperView{89.0f};
  static float kLowerView{-89.0f};
  camera.settings.pitch =
      std::clamp(camera.settings.pitch, kLowerView, kUpperView);

  camera.Update();
}

void PrespectiveCameraController::CallbackScroll(float y_offset) {
  static float kMaxZoom{45.0f};
  static float kMinZoom{1.0f};

  camera.settings.zoom -= y_offset;
  camera.settings.zoom = std::clamp(camera.settings.zoom, kMinZoom, kMaxZoom);

  camera.Update();
}

}  // namespace musashi
