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
  Init();
}

Game::~Game() noexcept {
  glfwTerminate();
  window_->Destory();
  kRenderer->ShutDown();
  Stop();
}

void Game::Init() {
  glfwInit();
  window_->Create();
  kLogger->Trace("APPLICATION CREATED");
}

void Game::Run() {
  kRenderer->Init();
  kInput->Init(window_->GetHandler());

  running_ = true;

  time_.Init();

  while (running_) {
    window_->PollEvents();

    if (window_->ShouldClose()) {
      Stop();
      break;
    }

    time_.points.current_time = Time::GetTime();
    time_.points.elapsed_time =
        time_.points.current_time - time_.points.last_time;

    time_.points.last_time = time_.points.current_time;
    time_.points.accumulator += time_.points.elapsed_time;

    kInput->ProcessInput(window_->GetHandler(), time_.points.elapsed_time);

    while (time_.points.accumulator >= Time::kFixedDeltaTime) {
      Update(Time::kFixedDeltaTime);
      time_.points.accumulator -= Time::kFixedDeltaTime;
    }

    kRenderer->Render();

    window_->Update();
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
