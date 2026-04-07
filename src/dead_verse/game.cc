#include "game.h"
#include "global.h"

#include "platform/input.h"
#include "renderer/renderer.h"
#include "states/game_state.h"
#include "util/log.h"

namespace musashi {

Game::Game(const GameSpecification& specs)
    : window_(std::make_shared<Window>(specs.window_specs)),
      specifications_(specs) {
  glfwInit();
  window_->Create();
  kGlobal.logger->Trace("APPLICATION CREATED");
}

Game::~Game() noexcept {
  glfwTerminate();
  window_->Destory();
  kGlobal.renderer->ShutDown();
  kGlobal.game->Stop();
}

void Game::Run() {
  running_ = true;
  kGlobal.input->Init(window_->GetHandler());
  kGlobal.logger->Trace("APPLICATION RUNNING");

  kGlobal.renderer->AddShader("../../assets/shaders/object/vert.glsl",
                              "../../assets/shaders/object/frag.glsl");

  glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  while (running_) {
    if (window_->ShouldClose()) {
      Stop();
      break;
    }

    // TODO: First render, then play with ticks and deltas.
    kGlobal.input->ProcessInput(window_->GetHandler());

    // kGlobal.state->Update();

    kGlobal.renderer->Render(0.0f);
    // kGlobal.renderer->Render();

    window_->Update();
    window_->PollEvents();
  }
}
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

};  // namespace musashi
