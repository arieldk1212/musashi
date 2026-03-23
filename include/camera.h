#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>

enum class CameraMovement : uint8_t { FORWARD, BACKWARD, RIGHT, LEFT };

// Default Values
constexpr float kYaw{-90.0f};
constexpr float kPitch{0.0f};
constexpr float kZoom{45.0f}; // FOV
constexpr float kSpeed = 2.5f;
constexpr float kSensitivity{0.1f};

class Camera {
public:
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kYaw,
         float pitch = kPitch);
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  glm::vec3 Position;
  glm::vec3 Front{glm::vec3(0.0f, 0.0f, -1.0f)};
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;
  float Yaw;
  float Pitch;
  float Zoom{kZoom};
  float MovementSpeed{kSpeed};
  float MouseSensitivity{kSensitivity};

  glm::mat4 GetViewMatrix();
  void ProcessKeyboard(CameraMovement direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch = true);
  void ProcessMouseScroll(float yoffset);

private:
  void UpdateCameraVectors() {
    // Calculate new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    // Also re-calculate right and up vectors, because their length gets closer
    // to 0 the more you look up, result in slower movements.
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
  }
};

#endif