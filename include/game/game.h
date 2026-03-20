#ifndef GAME_H_
#define GAME_H_

#include <array>
#include <memory>
#include <string>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "shaders/shader.h"
#include "textures/texture.h"

namespace game {

template <auto F> struct delete_with {
  template <typename T> void operator()(T *x) { F(x); }
};

static float mixValue = 0.2f; // for opacity, 0.2 default
static constexpr int kGameWidth = 800;
static constexpr int kGameHeight = 600;

class Game {
public:
  Game(const std::string &window_title);
  ~Game();

  static inline void ProcessInput(GLFWwindow *window);
  static inline void FramebufferSizeCallback(GLFWwindow *window, int width,
                                             int height);
  static inline int GetMaxVertexAttributes();

  void Run();
  void Shaders(); // Init Shaders

private:
  unsigned int VAO_;
  unsigned int VBO_;
  unsigned int EBO_;
  std::string game_title_;
  // std::array<unsigned int, 2> vaos_;
  // std::array<unsigned int, 2> vbos_;
  std::unique_ptr<Shader> shader_;
  std::unique_ptr<Texture> texture_;
  // std::array<unsigned int, 2> shaders_;
};

}; // namespace game

#endif