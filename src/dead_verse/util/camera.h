#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace musashi {

enum class CameraMovement : uint8_t { kForward, kBackward, kRight, kLeft };

struct CameraDefaults {
  static constexpr float kYaw{-90.0f};
  static constexpr float kPitch{0.0f};
  static constexpr float kZoom{45.0f};
  static constexpr float kSpeed{2.5f};
  static constexpr float kSensitivity{0.1f};
  static constexpr float kCameraZStart{0.4f};
};

struct CameraSettings {
  bool first_mouse{true};
  float yaw{CameraDefaults::kYaw};
  float pitch{CameraDefaults::kPitch};
  float zoom{CameraDefaults::kZoom};
  float movement_speed{CameraDefaults::kSpeed};
  float mouse_sensitivity{CameraDefaults::kSensitivity};
};

struct CameraVectors {
  glm::vec3 right{};
  glm::vec3 world_up{};
  glm::vec3 up{glm::vec3(0.0f, 1.0f, 0.0f)};
  glm::vec3 front{glm::vec3(0.0f, 0.0f, -1.0f)};
};

struct Camera {
  virtual ~Camera() = default;

  virtual void Update() = 0;

  virtual void SetPosition(const glm::vec3& position) = 0;

  virtual const glm::mat4& GetViewMatrix() = 0;
  virtual const glm::mat4& GetProjectionMatrix() = 0;
  virtual const glm::mat4& GetViewProjectionMatrix() = 0;
};

struct PrespectiveCamera : public Camera {
  explicit PrespectiveCamera(const glm::vec3& position);

  void Update() override;

  void SetPosition(const glm::vec3& new_position) override {
    position = new_position;
    Update();
  }

  const glm::mat4& GetViewMatrix() override { return view_matrix; }
  [[nodiscard]] glm::mat4 CalculateNewViewMatrix() const {
    return glm::lookAt(position, position + vectors.front, vectors.up);
  }
  const glm::mat4& GetProjectionMatrix() override { return projection_matrix; }
  const glm::mat4& GetViewProjectionMatrix() override {
    return view_projection_matrix;
  }

  CameraVectors vectors;
  CameraSettings settings;

  glm::vec3 position;
  glm::mat4 view_matrix;
  glm::mat4 projection_matrix;
  glm::mat4 view_projection_matrix;
  // Camera::CameraSettings settings;
};

struct PrespectiveCameraController {
  struct CameraMouseOffset {
    float last_x{0.0f};
    float last_y{0.0f};
  };

  explicit PrespectiveCameraController(
      const glm::vec3& position = glm::vec3(0.0f, 0.0f,
                                            CameraDefaults::kCameraZStart));

  void Init();
  // NOTE: API
  void Update(float delta_time);

  // NOTE: Dont use below
  void CallbackScroll(float y_offset);
  void CallbackMouse(double x_pos, double y_pos);
  void CameraProcessKeyboard(CameraMovement direction, float delta_time);

  PrespectiveCamera camera;
  CameraMouseOffset mouse_offset;
};

}  // namespace musashi

#endif
