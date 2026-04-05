#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
// clang-format on

namespace musashi {

constexpr int kDefaultWidth = 1920;
constexpr int kDefaultHeight = 1080;

struct WindowSpecification {
  bool vsync{false};
  bool is_resizeable{false};
  std::string title{"Window"};
  uint32_t width = kDefaultWidth;
  uint32_t height = kDefaultHeight;
};

class Window {
 public:
  explicit Window(const WindowSpecification& specs);
  ~Window();

  [[nodiscard]] static float GetTime() {
    return static_cast<float>(glfwGetTime());
  }
  void Create();
  void Destory();
  void Update();
  static void HandleCallback();
  [[nodiscard]] bool ShouldClose() const;

  [[nodiscard]] glm::vec2 GetMousePosition() const;
  [[nodiscard]] glm::vec2 GetFrameBufferSize() const;
  [[nodiscard]] GLFWwindow* GetHandle() const {
    if (window_ != nullptr) {
      return window_;
    }
    assert(false);
  }

 private:
  GLFWwindow* window_{nullptr};
  WindowSpecification specifications_;
};

}  // namespace musashi

#endif
