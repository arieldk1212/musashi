#ifndef GAME_H_
#define GAME_H_

#include "shaders/shader.h"
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
    "layout (location = 1) in vec3 aColor;\n"

    "out vec3 ourColorVertices;\n" // usage for coloring
    "out vec4 vertexColor;\n"      // usage for coloring

    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    // "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n" // color dark red
    "   ourColorVertices = aColor;\n"
    "}\0";

static const char *kFragmentShaderSource =
    "#version 330 core\n"
    "uniform vec4 ourColor;\n" // can define in any shader stage, but if we
    // define it we have to use it!

    "in vec3 ourColorVertices;\n" // pass as input
    "in vec4 vertexColor;\n"      // pass as input

    "out vec4 FragColor;\n"

    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColorVertices, 1.0);\n"
    // "   FragColor = ourColor;\n" // pass to the frag shader
    // "   FragColor = vertexColor;\n" // pass to the frag shader
    // "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

static unsigned int kEBO;

static unsigned int kVertexShader;
static unsigned int kFragmentShader;
static unsigned int kShaderProgram;

static inline void ProcessInput(GLFWwindow *window);
static inline void FramebufferSizeCallback(GLFWwindow *window, int width,
                                           int height);

static inline int GetMaxVertexAttributes() {
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  return nrAttributes;
}

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
  std::unique_ptr<Shader> shader_{nullptr};
  // std::array<unsigned int, 2> shaders_;
};

}; // namespace game

#endif