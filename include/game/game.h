#ifndef GAME_H_
#define GAME_H_

#include <memory>

#include "camera.h"
#include "shaders/shader.h" // glad before glfw
#include "textures/texture.h"

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

namespace game {

template <auto F> struct delete_with {
  template <typename T> void operator()(T *x) { F(x); }
};

static int GetMaxVertexAttributes();
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

static constexpr int kGameWidth = 800;
static constexpr int kGameHeight = 600;
static float kLastX{static_cast<float>(kGameWidth) /
                    2}; // width / 2 -> default mouse position x
static float kLastY{static_cast<float>(kGameHeight) /
                    2}; // height / 2 -> default mouse position y

static float kMixValue{0.2f}; // for opacity, 0.2 default

static bool kFirstMouse{true};
static float kDeltaTime{0.0f}; // Time between current frame and last frame
static float kLastFrame{0.0f};

class Game {
public:
  Game(const std::string &window_title);
  ~Game();

  void ProcessInput(GLFWwindow *window);

  static void MouseCallbackWrapper(GLFWwindow *window, double xpos,
                                   double ypos);
  static void ScrollCallbackWrapper(GLFWwindow *window, double xoffset,
                                    double yoffset);

  void Run();
  void Shaders();

private:
  void MouseCallback(GLFWwindow *window, double xpos, double ypos);
  void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

  GLuint VAO_;
  GLuint VBO_;
  std::string game_title_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<Shader> shader_;
  std::unique_ptr<Texture> texture_;
};

}; // namespace game

#endif