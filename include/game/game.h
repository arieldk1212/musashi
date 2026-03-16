#ifndef MUSASHI_INCLUDE_GAME_WINDOW_H_
#define MUSASHI_INCLUDE_GAME_WINDOW_H_

#include <array>
#include <memory>
#include <string>

#include <glad/glad.h>
//////////
#include <GLFW/glfw3.h>

namespace game {

template <auto F> struct delete_with {
  template <typename T> void operator()(T *x) { F(x); }
};

using Window = std::unique_ptr<GLFWwindow, delete_with<glfwDestroyWindow>>;

static constexpr int kGameWidth = 800;
static constexpr int kGameHeight = 600;

static const char *kVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static const char *kFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

static unsigned int kEBO;

static unsigned int kVertexShader;
static unsigned int kFragmentShader;
static unsigned int kShaderProgram;

static inline void ProcessInput(GLFWwindow *window);
static inline void FramebufferSizeCallback(GLFWwindow *window, int width,
                                           int height);

class Game {
public:
  Game(const std::string &window_title);
  ~Game();

  void Run();
  void Shaders();

private:
  int fps_{60};
  std::string game_title_;
  std::array<unsigned int, 2> vaos_;
  std::array<unsigned int, 2> vbos_;
  std::array<unsigned int, 2> shaders_;
};

}; // namespace game

#endif