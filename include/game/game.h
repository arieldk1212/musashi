#ifndef GAME_H_
#define GAME_H_

#include <memory>

#include "shaders/shader.h" // glad before glfw
#include "textures/texture.h"

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

namespace game {

template <auto F> struct delete_with {
  template <typename T> void operator()(T *x) { F(x); }
};

static float mixValue = 0.2f; // for opacity, 0.2 default
static constexpr int kGameWidth = 800;
static constexpr int kGameHeight = 600;

static float deltaTime = 0.0f; // Time between current frame and last frame
static float lastFrame = 0.0f;

static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

static bool firstMouse{true};
static float yaw{-90.0f};
static float pitch{0.0f};
static float lastX{400}; // width / 2 -> default mouse position x
static float lastY{300}; // height / 2 -> default mouse position y
static float fov{45.0f};

class Game {
public:
  Game(const std::string &window_title);
  ~Game();

  static inline void ProcessInput(GLFWwindow *window);
  static inline void FramebufferSizeCallback(GLFWwindow *window, int width,
                                             int height);
  static void MouseCallback(GLFWwindow *window, double xpos, double ypos);
  static void ScrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
  static inline int GetMaxVertexAttributes();

  void Run();
  void Shaders(); // Init Shaders

private:
  GLuint VAO_;
  GLuint VBO_;
  std::string game_title_;
  std::unique_ptr<Shader> shader_;
  std::unique_ptr<Texture> texture_;
};

}; // namespace game

#endif