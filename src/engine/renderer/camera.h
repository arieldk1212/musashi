#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace musashi {

enum class CameraMovement : uint8_t { kForward, kBackward, kRight, kLeft };

static constexpr float kCameraZStart{0.4f};

// Default Values
constexpr float kYaw{-90.0f};
constexpr float kPitch{0.0f};
constexpr float kZoom{45.0f};  // FOV
constexpr float kSpeed = 2.5f;
constexpr float kSensitivity{0.1f};

class Camera {
 public:
  explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kYaw,
                  float pitch = kPitch);
  Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
         float up_z, float yaw, float pitch);

  [[nodiscard]] glm::mat4 GetViewMatrix() const;
  [[nodiscard]] float GetZoom() const { return zoom_; }
  [[nodiscard]] const glm::vec3& GetFront() const { return front_; }
  [[nodiscard]] const glm::vec3& GetPosition() const { return position_; }

  void ProcessKeyboard(CameraMovement direction, float delta_time);
  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrain_pitch = true);
  void ProcessMouseScroll(float yoffset);

 private:
  void UpdateCameraVectors();

  glm::vec3 up_{};
  glm::vec3 right_{};
  glm::vec3 world_up_{};
  glm::vec3 position_{};
  glm::vec3 front_{glm::vec3(0.0f, 0.0f, -1.0f)};
  float yaw_{0.0f};
  float pitch_{0.0f};
  float zoom_{kZoom};
  float movement_speed_{kSpeed};
  float mouse_sensitivity_{kSensitivity};
};

}  // namespace musashi

#endif
