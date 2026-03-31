#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace musashi {

template <auto F>
struct DeleteWith {
  template <typename T>
  void operator()(T* x) {
    F(x);
  }
};

class Window {
 public:
  static constexpr int kWidth{1000};
  static constexpr int kHeight{800};
  enum class InputMode : uint8_t { kNormal, kHidden, kDisabled, kCaptured };

  explicit Window(std::string window_title);
  ~Window();

  [[nodiscard]] static float GetTime() {
    return static_cast<float>(glfwGetTime());
  }
  void OnUpdate();
  void SetInputMode(InputMode mode);
  void SetEventCallback();

 private:
  std::string title_;
  GLFWwindow* window_{nullptr};
};

}  // namespace musashi

#endif