#include <print>
#include <vector>

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

Game::~Game() {
  glDeleteVertexArrays(2, vaos_.data());
  glDeleteBuffers(2, vbos_.data());
  glDeleteProgram(kShaderProgram);
  glfwTerminate();
}

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

  glfwSetFramebufferSizeCallback(window.get(), FramebufferSizeCallback);

  Shaders();

  while (!glfwWindowShouldClose(window.get())) {

    ProcessInput(window.get());

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(kShaderProgram);

    glBindVertexArray(vaos_[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(vaos_[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window.get());
    glfwPollEvents();
  }
}

void Game::Shaders() {

  kVertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(kVertexShader, 1, &kVertexShaderSource, nullptr);
  glCompileShader(kVertexShader);

  int success;
  char info_log[512];
  glGetShaderiv(kVertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(kVertexShader, 512, NULL, info_log);
    std::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED, {}", info_log);
  }

  kFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(kFragmentShader, 1, &kFragmentShaderSource, NULL);
  glCompileShader(kFragmentShader);
  glGetShaderiv(kFragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(kFragmentShader, 512, NULL, info_log);
    std::println("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED, {}", info_log);
  }

  kShaderProgram = glCreateProgram();
  glAttachShader(kShaderProgram, kVertexShader);
  glAttachShader(kShaderProgram, kFragmentShader);
  glLinkProgram(kShaderProgram);
  glGetProgramiv(kShaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(kShaderProgram, 512, NULL, info_log);
    std::println("ERROR::SHADER::PROGRAM::LINKING_FAILED, {}", info_log);
  }
  glDeleteShader(kVertexShader);
  glDeleteShader(kFragmentShader);

  std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

  std::vector<float> vertices_exercise = {0.0f, -0.5f, 0.0f, 0.9f, -0.5f,
                                          0.0f, 0.45f, 0.5f, 0.0f};

  std::vector<float> vertices_rect = {0.5f,  0.5f,  0.0f, 0.5f,  -0.5f, 0.0f,
                                      -0.5f, -0.5f, 0.0f, -0.5f, 0.5f,  0.0f};

  std::vector<int> indices = {0, 1, 3, 1, 2, 3};

  glGenVertexArrays(2, vaos_.data());
  glGenBuffers(2, vbos_.data());
  // glGenBuffers(1, &kEBO);

  glBindVertexArray(vaos_[0]);
  glBindBuffer(GL_ARRAY_BUFFER, vbos_[0]);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               &vertices.front(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindVertexArray(vaos_[1]);
  glBindBuffer(GL_ARRAY_BUFFER, vbos_[1]);
  glBufferData(GL_ARRAY_BUFFER, vertices_exercise.size() * sizeof(float),
               &vertices_exercise.front(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  // glBufferData(GL_ARRAY_BUFFER, vertices_rect.size() * sizeof(float),
  //              vertices_rect.data(), GL_STATIC_DRAW);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
  //              indices.data(), GL_STATIC_DRAW);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);

  // glBindVertexArray(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
}; // namespace game