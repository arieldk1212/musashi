#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace musashi {

enum class CameraMovement : uint8_t { kForward, kBackward, kRight, kLeft };

static constexpr float kCameraZStart{0.4f};

constexpr float kYaw{-90.0f};
constexpr float kPitch{0.0f};
constexpr float kZoom{45.0f};  // FOV
constexpr float kSpeed = 2.5f;
constexpr float kSensitivity{0.1f};

struct Camera {
  explicit Camera(glm::vec3 p_position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f),
                  float p_yaw = kYaw, float p_pitch = kPitch);
  Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
         float up_z, float p_yaw, float p_pitch);

  [[nodiscard]] float GetZoom() const { return zoom; }
  [[nodiscard]] const glm::vec3& GetFront() const { return front; }
  [[nodiscard]] const glm::vec3& GetPosition() const { return position; }
  [[nodiscard]] glm::mat4 GetViewMatrix() const {
    return glm::lookAt(position, position + front, up);
  }

  // Calculate new front vector
  void UpdateCameraVectors();

  float yaw{0.0f};
  float pitch{0.0f};
  float zoom{kZoom};
  float movement_speed{kSpeed};
  float mouse_sensitivity{kSensitivity};

  glm::vec3 up{};
  glm::vec3 right{};
  glm::vec3 world_up{};
  glm::vec3 position{};
  glm::vec3 front{glm::vec3(0.0f, 0.0f, -1.0f)};
};

}  // namespace musashi

#endif
