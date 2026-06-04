#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>

// clang-format off
#include <glad/glad.h>
// clang-format on
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "util/log.h"

namespace musashi {

static constexpr int kDefaultWidth = 1920;
static constexpr int kDefaultHeight = 1080;
static constexpr const char* kGlslVersion = "#version 330";

struct WindowSpecification {
  bool vsync{false};
  bool is_resizeable{false};
  std::string title{"Dead Verse"};
  uint32_t width{kDefaultWidth};
  uint32_t height{kDefaultHeight};
};

class Window {
 public:
  explicit Window(Logger& logger, const WindowSpecification& specs);
  ~Window();

  void Create();
  void Destroy();
  void Update();
  void SetShouldClose();
  [[nodiscard]] bool ShouldClose() const;
  void SetVSync(bool status);
  void PollEvents();
  void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

  [[nodiscard]] glm::vec2 GetFrameBufferSize() const;
  [[nodiscard]] GLFWwindow* GetHandler() const {
    if (window_ != nullptr) {
      return window_;
    }
    assert(false);
  }

  [[nodiscard]] float GetWindowResolutionWidth() const {
    return static_cast<float>(specifications_.width);
  }
  [[nodiscard]] float GetWindowResolutionHeight() const {
    return static_cast<float>(specifications_.height);
  }

 private:
  Logger* logger_;
  GLFWwindow* window_{nullptr};
  WindowSpecification specifications_;
};

}  // namespace musashi

#endif
