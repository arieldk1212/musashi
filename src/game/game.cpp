#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "game/game.h"

namespace game {

int GetMaxVertexAttributes() {
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  return nrAttributes;
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
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

void Game::ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    kMixValue += 0.001f;
    if (kMixValue >= 1.0f) {
      kMixValue = 1.0f;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    kMixValue -= 0.001f;
    if (kMixValue <= 0.0f) {
      kMixValue = 0.0f;
    }
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera_->ProcessKeyboard(CameraMovement::FORWARD, kDeltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera_->ProcessKeyboard(CameraMovement::BACKWARD, kDeltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera_->ProcessKeyboard(CameraMovement::LEFT, kDeltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera_->ProcessKeyboard(CameraMovement::RIGHT, kDeltaTime);
}

void Game::MouseCallbackWrapper(GLFWwindow *window, double xpos, double ypos) {
  Game *instance = static_cast<Game *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->MouseCallback(window, xpos, ypos);
  }
}

void Game::ScrollCallbackWrapper(GLFWwindow *window, double xoffset,
                                 double yoffset) {
  Game *instance = static_cast<Game *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->ScrollCallback(window, xoffset, yoffset);
  }
}

void Game::MouseCallback(GLFWwindow *window, double xpos, double ypos) {
  /**
   * @brief steps to calc camera_'s direction vector
    1. Calculate the mouse's offset since the last frame.
    2. Add the offset values to the camera_'s yaw and pitch values.
    3. Add some constraints to the minimum/maximum pitch values (sensitivity).
    4. Calculate the direction vector.
   */

  xpos = static_cast<float>(xpos);
  ypos = static_cast<float>(ypos);

  if (kFirstMouse) {
    kLastX = xpos;
    kLastY = ypos;
    kFirstMouse = false;
  }

  float xoffset = xpos - kLastX;
  float yoffset =
      kLastY - ypos; // reversed, y-coordinates range from bottom to top

  kLastX = xpos;
  kLastY = ypos;

  camera_->ProcessMouseMovement(xoffset, yoffset);
}

void Game::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
  camera_->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Game::Run() {

  using Window = std::unique_ptr<GLFWwindow, delete_with<glfwDestroyWindow>>;

  Window window = Window(glfwCreateWindow(
      kGameWidth, kGameHeight, game_title_.c_str(), nullptr, nullptr));

  if (window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window.get());
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  glfwSetWindowUserPointer(window.get(), this); // for wrappers
  glfwSetFramebufferSizeCallback(window.get(), FramebufferSizeCallback);
  glfwSetCursorPosCallback(window.get(), MouseCallbackWrapper);
  glfwSetScrollCallback(window.get(), ScrollCallbackWrapper);
  glfwSetInputMode(window.get(), GLFW_CURSOR,
                   GLFW_CURSOR_DISABLED); // mouse wont
  // be visible and should not leave the screen

  glEnable(GL_DEPTH_TEST);

  shader_ = std::make_unique<Shader>("../../include/shaders/vertex.glsl",
                                     "../../include/shaders/fragment.glsl");
  texture_ = std::make_unique<Texture>();

  Shaders();

  texture_->AddTexture("../../assets/textures/wooden-container.jpg", false);
  texture_->AddTexture("../../assets/textures/awesomeface.png", true);

  shader_->use();

  camera_ = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 2.0f));

  for (int i{0}; i < texture_->Size(); ++i) {
    std::string texture = "ourTexture" + std::to_string(i);
    shader_->setInt(texture, i);
  }

  std::vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  // // Camera
  // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // z positive for
  // backwards glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); glm::vec3
  // cameraDirection = glm::normalize(
  //     cameraPos -
  //     cameraTarget); // it is basically pointing in the reverse
  //                    // direction of what it is targeting, because vector
  //                    // substraciton gives the the direction we want
  // glm::vec3 up = glm::vec3(0.0f, 0.1f, 0.0f); // define up vector
  // glm::vec3 cameraRight = glm::normalize(glm::cross(
  //     up,
  //     cameraDirection)); // then cross the up with and direction gives us the
  //     a
  //                        // direction that points in the positive x-axis
  //                        (right)
  //                        // (if we switch the order - negative x axis)
  // glm::vec3 cameraUp = glm::cross(
  //     cameraDirection, cameraRight); // now we can create the lookAt matrix

  // glm::mat4 view;
  // view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

  // if no need for FOV keep here, else move inside the loop
  // glm::mat4 projection = glm::perspective(
  //     glm::radians(fov), (float)kGameWidth / (float)kGameHeight, 0.1f,
  //     100.0f);
  // shader_->setMat4("projection", projection);

  // WE DO THAT IN THE MOUSE CALL BACK FUNCTION
  // glm::vec3 direction;
  // we also multiply x and z with cos of pitch, because when calculation pitch,
  // they are also inside the formula (as cos)
  // with these calculation we can transform pitch (up, down) and yaw (right,
  // left) values to 3D vector for looking around
  // direction.x = cos(glm::radians(yaw)) *
  //               cos(glm::radians(
  //                   pitch)); // because z is on sin, x on cos, if we calc
  //                   them
  // direction.z = sin(glm::radians(yaw))
  //     cos(glm::radians(pitch));           // sin because z is on sin
  // direction.y = sin(glm::radians(pitch)); // sin because the cos is the xz
  // axis yaw = -90.0f // by default because the world scene is towards the -z
  // axis, so we make sure the camera_ points towards the negative

  while (!glfwWindowShouldClose(window.get())) {

    float currentTime = static_cast<float>(glfwGetTime());
    kDeltaTime = currentTime - kLastFrame;
    kLastFrame = currentTime;

    ProcessInput(window.get());

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i{0}; i < texture_->Size(); ++i) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, texture_->Get(i));
    }

    shader_->setFloat("kMixValue", kMixValue);

    shader_->use();

    glm::mat4 view;
    view = camera_->GetViewMatrix();
    shader_->setMat4("view", view);

    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->Zoom),
                         (float)kGameWidth / (float)kGameHeight, 0.1f, 100.0f);
    shader_->setMat4("projection", projection);

    glBindVertexArray(VAO_);

    for (unsigned int i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      if (i % 2 == 1) {
        model = glm::rotate(model, (float)glfwGetTime(),
                            glm::vec3(1.0f, 0.3f, 0.5f));
      } else {
        model = glm::rotate(model, glm::radians(angle),
                            glm::vec3(1.0f, 0.3f, 0.5f));
      }
      shader_->setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window.get());
    glfwPollEvents();
  }
}

void Game::Shaders() {
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

  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);

  glBindVertexArray(VAO_);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, vertices_cube.size() * sizeof(float),
               vertices_cube.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));

  glEnableVertexAttribArray(1);
}

}; // namespace game