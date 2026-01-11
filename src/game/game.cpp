#include "game/game.h"
#include <GLFW/glfw3.h>

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
  GLFWwindow *window = glfwCreateWindow(kGameWidth, kGameHeight,
                                        game_title_.c_str(), NULL, NULL);

  if (window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  glViewport(0, 0, kGameWidth, kGameHeight);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

  while (!glfwWindowShouldClose(window)) {

    ProcessInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Game::Vertex() {

  std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(),
               GL_STATIC_DRAW);
}

}; // namespace game