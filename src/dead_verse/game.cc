#include "game.h"
#include "global.h"

#include "entity/component_manager.h"
#include "entity/components.h"
#include "platform/input.h"
#include "renderer/renderer.h"
#include "states/game_state.h"
#include "util/log.h"
#include "util/time.h"

namespace musashi {

Game::Game(const GameSpecification& specs)
    : window_(std::make_shared<Window>(specs.window_specs)),
      specifications_(specs) {
  glfwInit();
  window_->Create();
  kLogger->Trace("APPLICATION CREATED");
}

Game::~Game() noexcept {
  glfwTerminate();
  window_->Destory();
  kRenderer->ShutDown();
  Stop();
}

void Game::Run() {
  running_ = true;
  kLogger->Trace("APPLICATION RUNNING");

  // auto me = kECManager->CreateEntity("Me");
  // kECManager->RegisterComponent<HealthComponent>(100);
  // kECManager->AddComponent(me.id, HealthComponent{});

  kInput->Init(window_->GetHandler());
  kRenderer->Init();

  float last_time{0};
  float elapsed_time{0};
  float delta_time{0};

  // TODO: Change after we have game logic.
  kRenderer->UseShader(ShaderName::kObjectShader);

  while (running_) {
    if (window_->ShouldClose()) {
      Stop();
      break;
    }

    // TODO: Refactor input.
    kInput->ProcessInput(window_->GetHandler());

    // TODO: Refactor to ticks.
    auto now = Time::GetTime();
    delta_time = now - last_time;
    elapsed_time += delta_time;
    last_time = now;

    while (elapsed_time >= kTicksPerSecond) {
      Update(elapsed_time);
      elapsed_time -= kTicksPerSecond;
    }

    kRenderer->Render();

    window_->Update();
    window_->PollEvents();
  }
}

void Game::Update(float ts) {}

//   while (!glfwWindowShouldClose(window.get())) {
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

//   }

};  // namespace musashi
