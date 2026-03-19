#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game/game.h"
#include "shaders/shader.h"

namespace game {

void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    mixValue += 0.001f; // change this value accordingly (might be too slow or
                        // too fast based on system hardware)
    if (mixValue >= 1.0f) {
      mixValue = 1.0f;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    mixValue -= 0.001f; // change this value accordingly (might be too slow or
                        // too fast based on system hardware)
    if (mixValue <= 0.0f) {
      mixValue = 0.0f;
    }
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
  // glDeleteProgram(kShaderProgram);
  shader_->delete_program();
  glfwTerminate();
}

void Game::Run() {

  using Window = std::unique_ptr<GLFWwindow, delete_with<glfwDestroyWindow>>;

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

  shader_ = std::make_unique<Shader>("../../include/shaders/vertex.glsl",
                                     "../../include/shaders/fragment.glsl");
  Shaders();

  texture_ = std::make_unique<Texture>();
  texture_->AddTexture("../../assets/textures/wooden-container.jpg", false);
  texture_->AddTexture("../../assets/textures/awesomeface.png", true);

  shader_->use();

  // simple trnasformation
  // glm::mat4 trans = glm::mat4(1.0f);
  // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
  // auto transformLoc = glGetUniformLocation(shader_->ID, "transform");
  // send 1 matrices, dont transpose the matrix
  // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

  for (int i{0}; i < texture_->Size(); ++i) {
    std::string texture = "ourTexture" + std::to_string(i);
    // glUniform1i(glGetUniformLocation(shader_->ID, texture.c_str()),
    //             i); // set it manually
    shader_->setInt(texture, i); // can also do like this
  }

  while (!glfwWindowShouldClose(window.get())) {

    ProcessInput(window.get());

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i{0}; i < texture_->Size(); ++i) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, texture_->Get(i));
    }

    shader_->setFloat("mixValue", mixValue);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans =
        glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    unsigned int transformLoc = glGetUniformLocation(shader_->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    shader_->use();
    glBindVertexArray(vaos_[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans = glm::mat4(1.0f); // reset it to identity matrix
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
    float scaleAmount = static_cast<float>(sin(glfwGetTime()));
    trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
    glUniformMatrix4fv(
        transformLoc, 1, GL_FALSE,
        &trans[0][0]); // this time take the matrix value array's first
                       // element as its memory pointer value
    // now we draw again
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // float timeValue = glfwGetTime();
    // float greenValue = sin(timeValue) / 2.0f + 0.5f;
    // OLD CODE before shader class
    // int vertexColorLocation = glGetUniformLocation(kShaderProgram,
    // "ourColor"); glUniform4f(vertexColorLocation, 0.0f, greenValue,
    // 0.0f, 1.0f);
    shader_->setFloat("ourColorVertices", 1.0f);

    // auto transformLoc = glGetUniformLocation(shader_->ID, "transform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    // shader_->setMat4("transform", trans);

    // render the triangle
    // glBindVertexArray(vaos_[0]); // VAO if no need vaos_
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(vaos_[1]);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers and poll io events.
    glfwSwapBuffers(window.get());
    glfwPollEvents();
  }
}

void Game::Shaders() {
  std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

  std::vector<int> indices = {0, 1, 3, 1, 2, 3};

  std::vector<float> vertices_colored = {
      // dont forget to adjust the shader as well! glsl file.
      // if we do that we need to increase the offset for the strides because we
      // added another 3 floats to the VBO's memory
      // X Y Z R G B -> total stride = 24, offset for vertices is 0, offset for
      // color is 12.
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // last three are color
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // also here
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f}; // and here

  // 1 row == first 3 positions, then 3 color, then 2 texture coords.
  // 0,0 bottom left, 1,1 top right of texture coords.
  // total stride = 3 + 3 + 2 = 8 * 4 (float) = 32
  // positio offset = 0, color = 12, texture = 24
  std::vector<float> vertices_texture = {
      0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f,  1.0f, 0.5f, -0.5f, 0.0f,
      0.0f, 1.0f, 0.0f,  1.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f,
      0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 1.0f,  1.0f,  0.0f, 0.0f, 1.0f};

  glGenVertexArrays(2, vaos_.data());
  glGenBuffers(2, vbos_.data());
  glGenBuffers(1, &kEBO);

  glBindVertexArray(vaos_[0]);

  glBindBuffer(GL_ARRAY_BUFFER, vbos_[0]);
  glBufferData(GL_ARRAY_BUFFER, vertices_texture.size() * sizeof(float),
               vertices_texture.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
               indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // we do that because we added colors to the vertices vector.
  // dont forget to change to the right vector at glBufferData()!
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // now for our new we add the texture in the stride
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // to add another triangle: we use the second location on the arrays
  // transformation exercise
  // glBindVertexArray(vaos_[1]);

  // glBindBuffer(GL_ARRAY_BUFFER, vbos_[1]);
  // glBufferData(GL_ARRAY_BUFFER, vertices_texture.size() * sizeof(float),
  //              &vertices_texture.front(), GL_STATIC_DRAW);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  // glEnableVertexAttribArray(0);

  // glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(float),
  // indices.data(),
  //              GL_STATIC_DRAW);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);

  // glBindVertexArray(0);

  // no fill of color
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
}

void Game::Textures() {}

}; // namespace game