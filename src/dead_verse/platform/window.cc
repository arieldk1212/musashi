#include "global.h"
#include "window.h"

#include "util/log.h"

namespace musashi {

Window::Window(const WindowSpecification& specs)
    : specifications_(specs) {}

Window::~Window() {
  Destory();
}

void Window::Create() {
  if (!glfwInit()) {
    kGlobal.logger->Critical("Failed to initialize GLFW");
    assert(false);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window_ = glfwCreateWindow(static_cast<int>(specifications_.width),
                             static_cast<int>(specifications_.height),
                             specifications_.title.c_str(), nullptr, nullptr);
  if (window_ == nullptr) {
    glfwTerminate();
    kGlobal.logger->Critical("Failed to create GLFW window");
    assert(false);
  }
  glfwMakeContextCurrent(window_);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    kGlobal.logger->Critical("Failed to initialize GLAD");
    assert(false);
  }

  glfwMakeContextCurrent(window_);
  glfwSetWindowUserPointer(window_, this);

  glEnable(GL_DEPTH_TEST);
}

void Window::Destory() {
  if (window_ != nullptr) {
    glfwDestroyWindow(window_);
  }
  window_ = nullptr;
}

void Window::Update() {
  glfwSwapBuffers(window_);
}

bool Window::ShouldClose() const {
  return glfwWindowShouldClose(window_) != 0;
}

glm::vec2 Window::GetFrameBufferSize() const {
  int width{0};
  int height{0};
  glfwGetFramebufferSize(window_, &width, &height);
  return {width, height};
}

}  // namespace musashi
