#include "application.h"
#include "global.h"

#include "platform/input.h"
#include "renderer/renderer.h"
#include "util/log.h"

namespace musashi {

Application::Application(const ApplicationSpecification& specs)
    : window_(std::make_shared<Window>(specs.window_specs)),
      specifications_(specs) {
  glfwInit();
  window_->Create();
  kGlobal.logger->Trace("APPLICATION CREATED");
}

Application::~Application() noexcept {
  glfwTerminate();
  window_->Destory();
  kGlobal.logger->Trace("APPLICATION DESTROYED");
  kGlobal.application->Stop();
}

void Application::Run() {
  running_ = true;
  kGlobal.logger->Trace("APPLICATION RUNNING");

  while (running_) {
    glfwPollEvents();

    kGlobal.input->ProcessInput(window_->GetHandler());
    if (window_->ShouldClose()) {
      Stop();
      break;
    }

    kGlobal.renderer->Update();
    kGlobal.renderer->Render();

    window_->Update();
  }
}

// int App::GetMaxVertexAttributes() {
//   int nr_attributes{0};
//   glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nr_attributes);
//   return nr_attributes;
// }

// void App::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
// {
//   glViewport(0, 0, width, height);
// }

// App::~App() {
//   glDeleteVertexArrays(1, &VAO_);
//   glDeleteVertexArrays(1, &LightVAO_);
//   glDeleteBuffers(1, &VBO_);
//   shader_->DeleteProgram();
//   glfwTerminate();
// }

// void App::ProcessInput(GLFWwindow* window) {
//   if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//     glfwSetWindowShouldClose(window, true);
//   }

//   if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
//     extras::show_imgui = true;
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//   }

//   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//     if (extras::show_imgui) {
//       extras::show_imgui = false;
//       glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//     }
//   }

//   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//     camera_->ProcessKeyboard(CameraMovement::kForward, extras::delta_time);
//   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//     camera_->ProcessKeyboard(CameraMovement::kBackward, extras::delta_time);
//   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//     camera_->ProcessKeyboard(CameraMovement::kLeft, extras::delta_time);

//   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//     camera_->ProcessKeyboard(CameraMovement::kRight, extras::delta_time);
// }

// void App::MouseCallbackWrapper(GLFWwindow* window, double xpos, double ypos)
// {
//   App* instance = static_cast<App*>(glfwGetWindowUserPointer(window));
//   if (instance != nullptr) {
//     instance->MouseCallback(window, xpos, ypos);
//   }
// }

// void App::ScrollCallbackWrapper(GLFWwindow* window, double xoffset,
//                                 double yoffset) {
//   App* instance = static_cast<App*>(glfwGetWindowUserPointer(window));
//   if (instance != nullptr) {
//     instance->ScrollCallback(window, xoffset, yoffset);
//   }
// }

// void App::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
//   xpos = static_cast<float>(xpos);
//   ypos = static_cast<float>(ypos);

//   if (extras::first_mouse) {
//     extras::last_x = xpos;
//     extras::last_y = ypos;
//     extras::first_mouse = false;
//   }

//   float xoffset = xpos - extras::last_x;
//   float yoffset = extras::last_y -
//                   ypos;  // reversed, y-coordinates range from bottom to top

//   extras::last_x = xpos;
//   extras::last_y = ypos;

//   if (!extras::show_imgui) {
//     camera_->ProcessMouseMovement(xoffset, yoffset);
//   }
// }

// void App::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
// {
//   camera_->ProcessMouseScroll(static_cast<float>(yoffset));
// }

// void App::Run() {
//   using Window = std::unique_ptr<GLFWwindow, DeleteWith<glfwDestroyWindow>>;

//   Window window = Window(glfwCreateWindow(
//       kGameWidth, kGameHeight, game_title_.c_str(), nullptr, nullptr));

//   if (window == nullptr) {
//     glfwTerminate();
//     throw std::runtime_error("Failed to create GLFW window");
//   }

//   glfwMakeContextCurrent(window.get());
//   if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) ==
//       0) {
//     throw std::runtime_error("Failed to initialize GLAD");
//   }

//   glfwSetWindowUserPointer(window.get(), this);  // for callback's wrapper
//   glfwSetFramebufferSizeCallback(window.get(), FramebufferSizeCallback);
//   glfwSetCursorPosCallback(window.get(), MouseCallbackWrapper);
//   glfwSetScrollCallback(window.get(), ScrollCallbackWrapper);
//   glfwSetInputMode(window.get(), GLFW_CURSOR,
//                    GLFW_CURSOR_DISABLED);  // mouse wont
//   // be visible and should not leave the screen

//   stbi_set_flip_vertically_on_load(true);

//   glEnable(GL_DEPTH_TEST);

//   shader_ = std::make_unique<Shader>("../../assets/shaders/model_vert.glsl",
//                                      "../../assets/shaders/model_frag.glsl");

//   Model backpack("../../resources/objects/backpack/backpack.obj");

//   camera_ = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

//   Gui gui{window.get()};

//   while (!glfwWindowShouldClose(window.get())) {
//     auto current_time = static_cast<float>(glfwGetTime());
//     extras::delta_time = current_time - extras::last_frame;
//     extras::last_frame = current_time;

//     ProcessInput(window.get());

//     glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     Gui::SetFrame();

//     shader_->Use();

//     glm::mat4 projection = glm::perspective(
//         glm::radians(camera_->GetZoom()),
//         static_cast<float>(kGameWidth) / static_cast<float>(kGameHeight),
//         0.1f, 100.0f);
//     glm::mat4 view = camera_->GetViewMatrix();
//     shader_->SetMat4("projection", projection);
//     shader_->SetMat4("view", view);

//     auto model = glm::mat4(1.0f);
//     model = glm::translate(
//         model,
//         glm::vec3(
//             0.0f, 0.0f,
//             0.0f));  // translate it down so it's at the center of the scene
//     model = glm::scale(
//         model,
//         glm::vec3(1.0f, 1.0f,
//                   1.0f));  // it's a bit too big for our scene, so scale it
//                   down
//     shader_->SetMat4("model", model);
//     backpack.Draw(*shader_);

//     if (extras::show_imgui) {
//       ImGui::Begin("Musashi");
//       ImGui::Text("Lighting");
//       ImGui::End();
//     }
//     ImGui::Render();
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//     glfwSwapBuffers(window.get());
//     glfwPollEvents();
//   }
// }

// void App::Shaders() {
//   std::vector<float> vertices_cube = {
//       // COORDINATES  - aPos (3) | NORMALS (3) | TEX CORD - aTexCoord (2) |
//       (can
//       // also add color)
//       // we will ignore the textures and only apply the normals.
//       // also better to represent it using glm::vec3
//       -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f,
//       0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
//       -1.0f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
//       -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f,
//       0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//       // each layers holds 6 vertices, each vertex holds the stuff above.

//       -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f,
//       0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f,
//       0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//       -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,
//       0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

//       -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f,
//       -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
//       0.0f, 1.0f, -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -0.5f,
//       -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, -1.0f,
//       0.0f, 0.0f, 1.0f, 0.0f,

//       0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f,
//       -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//       0.0f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//       0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f,
//       0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

//       -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f,
//       0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.0f, -1.0f,
//       0.0f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//       -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f,
//       0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

//       -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f,
//       0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
//       0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f,
//       0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//       0.0f, 0.0f, 1.0f};

//   // for VAO_
//   glGenVertexArrays(1, &VAO_);
//   glGenBuffers(1, &VBO_);

//   glBindBuffer(GL_ARRAY_BUFFER, VBO_);
//   glBufferData(GL_ARRAY_BUFFER, vertices_cube.size() * sizeof(float),
//                vertices_cube.data(), GL_STATIC_DRAW);

//   glBindVertexArray(VAO_);

//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//   (void*)0); glEnableVertexAttribArray(0); glVertexAttribPointer(1, 3,
//   GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//                         (void*)(3 * sizeof(float)));
//   glEnableVertexAttribArray(1);
//   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//                         (void*)(6 * sizeof(float)));
//   glEnableVertexAttribArray(2);

//   // for LightVAO_
//   glGenVertexArrays(1, &LightVAO_);
//   glBindVertexArray(LightVAO_);

//   glBindBuffer(GL_ARRAY_BUFFER,
//                VBO_);  // no need but we do it again for educational purposes

//   // we Use only the first 3 therefore the stride is 6 for source shaders (or
//   to
//   // something else if you add more)
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//   (void*)0); glEnableVertexAttribArray(0);
// }

};  // namespace musashi
