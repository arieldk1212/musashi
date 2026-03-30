#include "camera.h"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>

namespace musashi {

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : world_up_(up),
      position_(position),
      yaw_(yaw),
      pitch_(pitch) {
  UpdateCameraVectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
               float up_z, float yaw, float pitch)
    : yaw_(yaw),
      pitch_(pitch) {
  position_ = glm::vec3(pos_x, pos_y, pos_z);
  world_up_ = glm::vec3(up_x, up_y, up_z);
  UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::ProcessKeyboard(CameraMovement direction, float delta_time) {
  float velocity = movement_speed_ * delta_time;
  switch (direction) {
    case CameraMovement::kForward:
      position_ += velocity * front_;
      break;
    case CameraMovement::kBackward:
      position_ -= velocity * front_;
      break;
    case CameraMovement::kLeft:
      position_ -= velocity * right_;
      break;
    case CameraMovement::kRight:
      position_ += velocity * right_;
      break;
  }
  // position.y =
  // 0.0f; // <-- this one-liner keeps the user at the ground level (xz plane)
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrain_pitch) {
  xoffset *= mouse_sensitivity_;
  yoffset *= mouse_sensitivity_;

  yaw_ += xoffset;
  pitch_ += yoffset;

  if (constrain_pitch) {
    pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
  }

  UpdateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset) {
  zoom_ -= yoffset;
  zoom_ = std::clamp(zoom_, 1.0f, 45.0f);
}

void Camera::UpdateCameraVectors() {
  // Calculate new front vector
  glm::vec3 front;
  front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front.y = sin(glm::radians(pitch_));
  front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front_ = glm::normalize(front);

  // Also re-calculate right and up vectors, because their length gets closer
  // to 0 the more you look up, result in slower movements.
  right_ = glm::normalize(glm::cross(front, world_up_));
  up_ = glm::normalize(glm::cross(right_, front));
}

}  // namespace musashi