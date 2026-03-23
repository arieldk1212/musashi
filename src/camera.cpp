#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch) {
  UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch) {
  Position = glm::vec3(posX, posY, posZ);
  WorldUp = glm::vec3(upX, upY, upZ);
  Yaw = yaw;
  Pitch = pitch;
  UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltatime) {
  float velocity = MovementSpeed * deltatime;
  switch (direction) {
  case CameraMovement::FORWARD:
    Position += velocity * Front;
    break;
  case CameraMovement::BACKWARD:
    Position -= velocity * Front;
    break;
  case CameraMovement::LEFT:
    Position -= velocity * Right;
    break;
  case CameraMovement::RIGHT:
    Position += velocity * Right;
    break;
  }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  if (constrainPitch) {
    if (Pitch > 89.0f) {
      Pitch = 89.0f;
    }
    if (Pitch < -89.0f) {
      Pitch = -89.0f;
    }
  }

  UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
  Zoom -= yoffset;
  if (Zoom < 1.0f) {
    Zoom = 1.0f;
  }
  if (Zoom > 45.0f) {
    Zoom = 45.0f;
  }
}