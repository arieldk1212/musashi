// clang-format off
#include <glad/glad.h>
// clang-format on
//
#include "global.h"
#include "platform.h"
#include "window.h"

#include "util/log.h"

namespace musashi {

Window::Window(const WindowSpecification& specs)
    : specifications_(specs) {}

Window::~Window() {
  Destroy();
  kLogger->Trace("Window Destroyed");
}

void Window::Create() {
  if (!glfwInit()) {
    kLogger->Critical("Failed To Initialize GLFW");
    assert(false);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  if (specifications_.is_resizeable) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  }

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window_ = glfwCreateWindow(static_cast<int>(specifications_.width),
                             static_cast<int>(specifications_.height),
                             specifications_.title.c_str(), nullptr, nullptr);
  if (window_ == nullptr) {
    glfwTerminate();
    kLogger->Critical("Failed To Create GLFW Window");
    assert(false);
  }
  glfwMakeContextCurrent(window_);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    kLogger->Critical("Failed To Initialize Glad");
    assert(false);
  }

  glfwSetWindowUserPointer(window_, kPlatform);

  glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
  SetVSync(true);

  glfwSetWindowSize(window_, specifications_.width, specifications_.height);

  auto frame_buffer = GetFrameBufferSize();
  glViewport(0, 0, frame_buffer.x, frame_buffer.y);

  auto wrapper_frame_buffer = [](GLFWwindow* window, int width, int height) {
    static_cast<Platform*>(glfwGetWindowUserPointer(window))
        ->window->FramebufferSizeCallback(window, width, height);
  };
  glfwSetFramebufferSizeCallback(window_, wrapper_frame_buffer);
}

void Window::Destroy() {
  if (window_ != nullptr) {
    glfwDestroyWindow(window_);
  }
  window_ = nullptr;
}

void Window::Update() {
  glfwSwapBuffers(window_);
}

void Window::PollEvents() {
  glfwPollEvents();
}

void Window::SetVSync(bool status) {
  if (status) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  specifications_.vsync = status;
}

void Window::SetShouldClose() {
  glfwSetWindowShouldClose(window_, true);
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

void Window::FramebufferSizeCallback(GLFWwindow* window, int width,
                                     int height) {
  // kPlatform->window->specifications_.width = width;
  // kPlatform->window->specifications_.height = height;
  auto frame_buffer = kPlatform->window->GetFrameBufferSize();
  glViewport(0, 0, frame_buffer.x, frame_buffer.y);
}

}  // namespace musashi
