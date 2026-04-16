#include "camera.h"
#include "global.h"

#include "platform/input.h"
#include "platform/platform.h"

namespace musashi {

PrespectiveCamera::PrespectiveCamera(const glm::vec3& position)
    : position(position) {
  Update();
}

void PrespectiveCamera::Update() {
  glm::vec3 front;
  front.x = cos(glm::radians(settings.yaw)) * cos(glm::radians(settings.pitch));
  front.y = sin(glm::radians(settings.pitch));
  front.z = sin(glm::radians(settings.yaw)) * cos(glm::radians(settings.pitch));
  vectors.front = glm::normalize(front);

  // Also re-calculate right and up vectors, because their length gets closer
  // to 0 the more you look up, result in slower movements.
  vectors.right = glm::normalize(glm::cross(vectors.front, vectors.world_up));
  vectors.up = glm::normalize(glm::cross(vectors.right, vectors.front));
}

PrespectiveCameraController::PrespectiveCameraController(
    const glm::vec3& position)
    : camera(position) {}

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
}

}  // namespace musashi
