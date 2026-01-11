#include "game/game.h"

namespace game {

void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

Game::Game(const std::string &window_title) : game_title_(window_title) {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}
Game::~Game() { glfwTerminate(); }

void Game::Run() {

  Window window = Window(glfwCreateWindow(kGameWidth, kGameHeight,
                                          game_title_.c_str(), NULL, NULL));

  if (window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window.get());

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  glViewport(0, 0, kGameWidth, kGameHeight);
  glfwSetFramebufferSizeCallback(window.get(), FramebufferSizeCallback);

  Shaders();

  while (!glfwWindowShouldClose(window.get())) {

    ProcessInput(window.get());

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window.get());
    glfwPollEvents();
  }
}

void Game::Shaders() {

  std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

  glGenBuffers(1, &kVBO);
  glBindBuffer(GL_ARRAY_BUFFER, kVBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(),
               GL_STATIC_DRAW);

  kVertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(kVertexShader, 1, &kVertexShaderSource, nullptr);
  glCompileShader(kVertexShader);

  int success;
  char info_log[512];
  glGetShaderiv(kVertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(kVertexShader, 512, NULL, info_log);
  }

  kFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(kFragmentShader, 1, &kFragmentShaderSource, NULL);
  glCompileShader(kFragmentShader);
}

}; // namespace game