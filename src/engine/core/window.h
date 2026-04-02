#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace musashi {

constexpr int kDefaultWidth = 1920;
constexpr int kDefaultHeight = 1080;

struct WindowSpecification {
  bool vsync{false};
  bool is_resizeable{false};
  std::string title{"Default"};
  uint32_t width = kDefaultWidth;
  uint32_t height = kDefaultHeight;
};

template <auto F>
struct DeleteWith {
  template <typename T>
  void operator()(T* x) {
    F(x);
  }
};

class Window {
 public:
  enum class InputMode : uint8_t { kNormal, kHidden, kDisabled, kCaptured };

  explicit Window(std::string window_title);
  ~Window();

  [[nodiscard]] static float GetTime() {
    return static_cast<float>(glfwGetTime());
  }
  void Create();
  void Destory();
  void Update();

  void SetInputMode(InputMode mode);
  void SetEventCallback();

  bool ShouldClose();
  [[nodiscard]] GLFWwindow* GetHandle() const { return window_; }

 private:
  std::string title_;
  GLFWwindow* window_{nullptr};
};

}  // namespace musashi

#endif