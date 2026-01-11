#ifndef MUSASHI_INCLUDE_GAME_WINDOW_H_
#define MUSASHI_INCLUDE_GAME_WINDOW_H_

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <memory>
#include <print>
#include <string>
#include <vector>

namespace game {

template <auto F> struct delete_with {
  template <typename T> void operator()(T *x) { F(x); }
};

using Window = std::unique_ptr<GLFWwindow, delete_with<glfwDestroyWindow>>;

constexpr int kGameWidth = 800;
constexpr int kGameHeight = 600;

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
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

static unsigned int kVBO;
static unsigned int kVertexShader;
static unsigned int kFragmentShader;

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
};

}; // namespace game

#endif