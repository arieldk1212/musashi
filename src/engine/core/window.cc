#include "window.h"

namespace musashi {

Window::Window(std::string window_title)
    : title_(std::move(window_title)) {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to Initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window_ = glfwCreateWindow(kWidth, kHeight, title_.c_str(), nullptr, nullptr);
  if (window_ == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to Create GLFW Window");
  }
  glfwMakeContextCurrent(window_);
  if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) ==
      0) {
    throw std::runtime_error("Failed to Initialize GLAD");
  }

  glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
  glfwTerminate();
}

void Window::SetInputMode(InputMode mode) {
  switch (mode) {
    case InputMode::kNormal:
      glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      break;
    case InputMode::kDisabled:
      glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      break;
    default:
  }
}

}  // namespace musashi