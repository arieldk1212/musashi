#ifndef MUSASHI_INCLUDE_GAME_WINDOW_H_
#define MUSASHI_INCLUDE_GAME_WINDOW_H_

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <print>
#include <string>
#include <vector>

namespace game {

constexpr int kGameWidth = 800;
constexpr int kGameHeight = 600;

static unsigned int VBO;

static void ProcessInput(GLFWwindow *window);
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

class Game {
public:
  Game(const std::string &window_title);
  ~Game();

  void Run();

  void Vertex();

private:
  int fps_{60};
  std::string game_title_;
};

}; // namespace game

#endif