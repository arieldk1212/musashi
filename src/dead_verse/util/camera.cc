#include "camera.h"

namespace musashi {

Camera::Camera(glm::vec3 p_position, glm::vec3 p_up, float p_yaw, float p_pitch)
    : yaw(p_yaw),
      pitch(p_pitch),
      world_up(p_up),
      position(p_position) {
  Update();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
               float up_z, float p_yaw, float p_pitch)
    : yaw(p_yaw),
      pitch(p_pitch) {
  position = glm::vec3(pos_x, pos_y, pos_z);
  world_up = glm::vec3(up_x, up_y, up_z);
  Update();
}

void Camera::Update() {
  glm::vec3 f_front;
  f_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  f_front.y = sin(glm::radians(pitch));
  f_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(f_front);

  // Also re-calculate right and up vectors, because their length gets closer
  // to 0 the more you look up, result in slower movements.
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
}

}  // namespace musashi
