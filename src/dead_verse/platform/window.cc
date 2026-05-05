#include "window.h"

#include "platform/platform.h"

namespace musashi {

Window::Window(Logger& logger, const WindowSpecification& specs)
    : logger_(&logger),
      specifications_(specs) {}

Window::~Window() {
  Destroy();
  logger_->Trace("WINDOW DESTROYED");
}

void Window::Create() {
  if (!glfwInit()) {
    logger_->Critical("Failed To Initialize GLFW");
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
    logger_->Critical("Failed To Create GLFW Window");
    assert(false);
  }
  glfwMakeContextCurrent(window_);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    logger_->Critical("Failed To Initialize Glad");
    assert(false);
  }

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
  auto frame_buffer = GetFrameBufferSize();
  glViewport(0, 0, frame_buffer.x, frame_buffer.y);
}

}  // namespace musashi
