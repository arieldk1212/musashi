#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game/game.h"
#include "shaders/shader.h"
#include "textures/texture.h"

// clang-format off

// Coordinate System
// to create a orthographic projection matrix do the following
// first 2 params are left and right, second 2 are top and bottom, they create
// the far and near plane 
// the last 2 define the distance between the near and far plane

// glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

// to calc prespective: out = (x/w, y/w, z/w)
// the w component is important for that reason
// the result from this are in the NDC range (normalized device space).
// can be created with the following:
// first param is FOV (how large the view space is), second is aspect ratio
//    calc by deviding the viewport height and width,
//    3, 4 params are the near and far plane.

// glm::mat4 proj = glm::prespective(glm::radians(45.0f), 
//    (float)width/(float)height, 0.1f, 100.0f);

// orthographic projection - each of the vertex coordinates are directly mapped
// to clip space without any fancy perspective division (it still does
// perspective division, but the w component is not manipulated (it stays 1) and
// thus has no effect). Because the orthographic projection doesn't use
// perspective projection, objects farther away do not seem smaller, which
// produces a weird visual output. For this reason the orthographic projection
// is mainly used for 2D renderings and for some architectural or engineering
// applications where we'd rather not have vertices distorted by perspective

// We create a transformation matrix for each of the aforementioned steps:
// model, view and projection matrix. A vertex coordinate is then transformed to
// clip coordinates as follows:
// clipVec = projMat * viewMat * modelMat * localVec
// then we assing to gl_Position.

// And then?
// The output of the vertex shader requires the coordinates to be in clip-space
// which is what we just did with the transformation matrices. OpenGL then
// performs perspective division on the clip-space coordinates to transform them
// to normalized-device coordinates. OpenGL then uses the parameters from
// glViewPort to map the normalized-device coordinates to screen coordinates
// where each coordinate corresponds to a point on your screen (in our case a
// 800x600 screen). This process is called the viewport transform.

// clang-format on

namespace game {

void Game::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void Game::ProcessInput(GLFWwindow *window) {
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

int Game::GetMaxVertexAttributes() {
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  return nrAttributes;
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
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
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

  glEnable(GL_DEPTH_TEST);

  shader_ = std::make_unique<Shader>("../../include/shaders/vertex.glsl",
                                     "../../include/shaders/fragment.glsl");
  texture_ = std::make_unique<Texture>();

  Shaders();

  texture_->AddTexture("../../assets/textures/wooden-container.jpg", false);
  texture_->AddTexture("../../assets/textures/awesomeface.png", true);

  shader_->use();

  for (int i{0}; i < texture_->Size(); ++i) {
    std::string texture = "ourTexture" + std::to_string(i);
    // glUniform1i(glGetUniformLocation(shader_->ID, texture.c_str()),
    //             i); // set it manually
    shader_->setInt(texture, i); // can also do like this
  }

  // simple trnasformation
  // glm::mat4 trans = glm::mat4(1.0f);
  // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
  // auto transformLoc = glGetUniformLocation(shader_->ID, "transform");
  // send 1 matrices, dont transpose the matrix
  // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

  while (!glfwWindowShouldClose(window.get())) {

    ProcessInput(window.get());

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i{0}; i < texture_->Size(); ++i) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, texture_->Get(i));
    }

    shader_->setFloat("mixValue", mixValue);

    shader_->use();

    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    // trans =
    //     glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f,
    //     0.0f, 1.0f));
    // unsigned int transformLoc = glGetUniformLocation(shader_->ID,
    // "transform"); glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
    // glm::value_ptr(trans));

    // glBindVertexArray(VAO_);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // trans = glm::mat4(1.0f); // reset it to identity matrix
    // trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
    // float scaleAmount = static_cast<float>(sin(glfwGetTime()));
    // trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount,
    // scaleAmount)); glUniformMatrix4fv(
    //     transformLoc, 1, GL_FALSE,
    //     &trans[0][0]); // this time take the matrix value array's first
    //                    // element as its memory pointer value
    // // now we draw again
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // !!3D!!
    // proj * view * model * local;
    // we first transform the model so it "looks" like its in the global world,
    // laying on the ground
    glm::mat4 model = glm::mat4(1.0f);
    model =
        glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0, 0.0f, 0.0f));
    // then we create the view matrix, so we can take the camera backwards or
    // the scene forward so that we can see the object
    // we move the scene by moving it on the Z axis towards the negative value.
    // took the scene forward so we can "see" the object.
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // next we define the projection matrix, we use perspective projection
    // becuase its a 3D app.
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(45.0f),
                         (float)kGameWidth / (float)kGameHeight, 0.1f, 100.f);
    // then we need to pass it to our shaders, usually done each frame
    unsigned int modelLoc = glGetUniformLocation(shader_->ID, "model");
    unsigned int viewLoc = glGetUniformLocation(shader_->ID, "view");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    shader_->setMat4("projection", projection);
    // now the model should be: a bit far back, titled towards the floor, a
    // little smaller.

    glBindVertexArray(VAO_);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // float timeValue = glfwGetTime();
    // float greenValue = sin(timeValue) / 2.0f + 0.5f;
    // OLD CODE before shader class
    // int vertexColorLocation = glGetUniformLocation(kShaderProgram,
    // "ourColor"); glUniform4f(vertexColorLocation, 0.0f, greenValue,
    // 0.0f, 1.0f);
    // shader_->setFloat("ourColorVertices", 1.0f);

    // auto transformLoc = glGetUniformLocation(shader_->ID, "transform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    // shader_->setMat4("transform", trans);

    // render the triangle
    // glBindVertexArray(vaos_[0]); // VAO if no need vaos_
    // glDrawArrays(GL_TRIANGLES, 0, 36);
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

  std::vector<float> vertices_cube = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  // glGenVertexArrays(2, vaos_.data());
  // glGenBuffers(2, vbos_.data());
  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);
  // glGenBuffers(1, &EBO_);

  glBindVertexArray(VAO_);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, vertices_cube.size() * sizeof(float),
               vertices_cube.data(), GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
  //              indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // we do that because we added colors to the vertices vector.
  // dont forget to change to the right vector at glBufferData()!
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // now for our new we add the texture in the stride
  // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
  //                       (void *)(6 * sizeof(float)));
  // glEnableVertexAttribArray(2);

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
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);

  // glBindVertexArray(0);

  // no fill of color
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
}

}; // namespace game