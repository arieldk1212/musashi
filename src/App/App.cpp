#include <cmath>
#include <imgui.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "App.h"
#include "Gui/Gui.h"

namespace Musashi {

int GetMaxVertexAttributes() {
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  return nrAttributes;
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

App::App(const std::string &window_title) : game_title_(window_title) {
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

App::~App() {
  glDeleteVertexArrays(1, &VAO_);
  glDeleteVertexArrays(1, &LightVAO_);
  glDeleteBuffers(1, &VBO_);
  shader_->delete_program();
  glfwTerminate();
}

void App::ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
    kShowImGui = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    if (kShowImGui) {
      kShowImGui = false;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

void App::MouseCallbackWrapper(GLFWwindow *window, double xpos, double ypos) {
  App *instance = static_cast<App *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->MouseCallback(window, xpos, ypos);
  }
}

void App::ScrollCallbackWrapper(GLFWwindow *window, double xoffset,
                                double yoffset) {
  App *instance = static_cast<App *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->ScrollCallback(window, xoffset, yoffset);
  }
}

void App::MouseCallback(GLFWwindow *window, double xpos, double ypos) {
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

  if (!kShowImGui) {
    camera_->ProcessMouseMovement(xoffset, yoffset);
  }
}

void App::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
  camera_->ProcessMouseScroll(static_cast<float>(yoffset));
}

void App::Run() {

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

  glfwSetWindowUserPointer(window.get(), this); // for callback's wrapper
  glfwSetFramebufferSizeCallback(window.get(), FramebufferSizeCallback);
  glfwSetCursorPosCallback(window.get(), MouseCallbackWrapper);
  glfwSetScrollCallback(window.get(), ScrollCallbackWrapper);
  glfwSetInputMode(window.get(), GLFW_CURSOR,
                   GLFW_CURSOR_DISABLED); // mouse wont
  // be visible and should not leave the screen

  glEnable(GL_DEPTH_TEST);

  shader_ = std::make_unique<Shader>("../../assets/shaders/vert.glsl",
                                     "../../assets/shaders/frag.glsl");
  light_shader_ =
      std::make_unique<Shader>("../../assets/shaders/source_vert.glsl",
                               "../../assets/shaders/source_frag.glsl");
  texture_ = std::make_unique<Texture>();

  Shaders();

  // texture_->AddTexture("../../assets/textures/wooden-container.jpg", false);
  // texture_->AddTexture("../../assets/textures/awesomeface.png", true);
  // texture_->AddTexture("../../assets/textures/container2.png", false);
  auto containerTexture =
      texture_->AddTexture("../../assets/textures/container2.png", false);
  // texture_->AddTexture("../../assets/textures/lighting_maps_specular_color.png",
  //                      false);
  auto containerSpecularTexture = texture_->AddTexture(
      "../../assets/textures/container2_specular.png", false);
  // auto matrixTexture =
  //     texture_->AddTexture("../../assets/textures/matrix.jpg", false);

  camera_ = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

  // for (int i{0}; i < texture_->Size(); ++i) {
  //   std::string texture = "ourTexture" + std::to_string(i);
  //   shader_->setInt(texture, i);
  // }
  shader_->use(); // dont forget to use!
  shader_->setInt("material.diffuse",
                  0); // if we have one special (texture)
  shader_->setInt("material.specular", 1);
  shader_->setFloat("light.constant", 1.0f);
  // shader_->setInt("material.emission", matrixTexture); // matrix texture

  std::vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  Gui gui{window.get()};

  while (!glfwWindowShouldClose(window.get())) {

    float currentTime = static_cast<float>(glfwGetTime());
    kDeltaTime = currentTime - kLastFrame;
    kLastFrame = currentTime;

    ProcessInput(window.get());

    glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gui.SetFrame();

    // glm::vec3 changingLightColor;
    // changingLightColor.x = sin(glfwGetTime() * 2.0f);
    // changingLightColor.y = sin(glfwGetTime() * 0.7f);
    // changingLightColor.z = sin(glfwGetTime() * 1.3f);

    // glm::vec3 diffuseColor = changingLightColor * glm::vec3(0.5f);
    // glm::vec3 ambientColor = changingLightColor * glm::vec3(0.2f);

    shader_->use();
    // shader_->setVec3("light.position", lightPos); // prob static
    // shader_->setVec3("light.direction", lightDirection);
    shader_->setVec3("ViewPos", camera_->Position);

    // to calculate the flashlight (spotlights)
    shader_->setVec3("light.position", camera_->Position); // prob static
    shader_->setVec3("light.direction", camera_->Front);
    shader_->setFloat(
        "light.cutOff",
        glm::cos(glm::radians(12.5f))); // optimized to calc the cos here
    shader_->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

    shader_->setVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    shader_->setVec3("light.diffuse",
                     glm::vec3(0.8f, 0.8f, 0.8f)); // darken diffuse light a bit
    shader_->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_->setFloat("light.linear", 0.09f);
    shader_->setFloat("light.quadratic", 0.032f);

    // shader_->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    // shader_->setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    // shader_->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader_->setFloat("material.shininess", 32.0f);

    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->Zoom),
                         (float)kGameWidth / (float)kGameHeight, 0.1f, 100.0f);
    glm::mat4 view = camera_->GetViewMatrix();
    shader_->setMat4("projection", projection);
    shader_->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader_->setMat4("model", model);

    for (int i{0}; i < texture_->Size(); ++i) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, texture_->Get(i));
    }

    glBindVertexArray(VAO_);
    for (unsigned int i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model =
          glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      shader_->setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // light object is weird with directional light, dont render.
    lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
    lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
    light_shader_->use();
    light_shader_->setVec3("LightColor", lightColor);
    light_shader_->setMat4("projection", projection);
    light_shader_->setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // smaller cube
    light_shader_->setMat4("model", model);

    glBindVertexArray(LightVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    if (kShowImGui) {
      ImGui::Begin("Musashi");
      ImGui::Text("Lighting");
      ImGui::ColorEdit3("Object Color", glm::value_ptr(objectColor));
      ImGui::ColorEdit3("Light Color", glm::value_ptr(lightColor));
      ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window.get());
    glfwPollEvents();
  }
}

void App::Shaders() {
  std::vector<float> vertices_cube = {
      // COORDINATES  - aPos (3) | NORMALS (3) | TEX CORD - aTexCoord (2) | (can
      // also add color)
      // we will ignore the textures and only apply the normals.
      // also better to represent it using glm::vec3
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
      0.0f,  -1.0f, 1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
      0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
      -0.5f, -1.0f, 0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
      0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
      0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      -1.0f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
      1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f};

  // for VAO_
  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, vertices_cube.size() * sizeof(float),
               vertices_cube.data(), GL_STATIC_DRAW);

  glBindVertexArray(VAO_);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // for LightVAO_
  glGenVertexArrays(1, &LightVAO_);
  glBindVertexArray(LightVAO_);

  glBindBuffer(GL_ARRAY_BUFFER,
               VBO_); // no need but we do it again for educational purposes

  // we use only the first 3 therefore the stride is 6 for source shaders (or to
  // something else if you add more)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

}; // namespace Musashi