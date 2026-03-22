#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>

enum class CameraMovement : uint8_t { FORWAD, BACKWARD, RIGHT, LEFT };

constexpr float kYaw{-90.0f};
constexpr float kPitch{0.0f};
constexpr float kSensitivity{0.1f};
constexpr float kZoom{45.0f}; // FOV

class Camera {
public:
private:
};

#endif