#include "game.h"
#include "global.h"

#include "platform/platform.h"
#include "renderer/renderer.h"
#include "util/log.h"
#include "util/time.h"

namespace musashi {

Game::Game(const GameSpecification& specs)
    : specifications_(specs) {
  Init();
}

Game::~Game() noexcept {
  glfwTerminate();
  kPlatform->Destroy();
  kRenderer->ShutDown();
  Stop();
}

void Game::Init() {
  glfwInit();
  kPlatform->Init();
  kLogger->Trace("APPLICATION CREATED");
}

void Game::Run() {
  kRenderer->Init();

  running_ = true;

  time_.Init();

  while (running_) {
    kPlatform->window->PollEvents();

    if (kPlatform->window->ShouldClose()) {
      Stop();
      break;
    }

    time_.points.current_time = Time::GetTime();
    time_.points.delta_time =
        time_.points.current_time - time_.points.last_time;
    time_.points.last_time = time_.points.current_time;

    time_.points.elapsed_time += time_.points.delta_time;

    while (time_.points.elapsed_time >= Time::kFixedDeltaTime) {
      Update(Time::kFixedDeltaTime);
      time_.points.elapsed_time -= Time::kFixedDeltaTime;
    }

    kPlatform->camera.Update(time_.points.delta_time);

    kRenderer->Render();
    kPlatform->window->Update();
  }
}

void Game::Update(float ts) {
  // TODO: Play with states here.
  // auto& cube_input_component =
  //     kECManager->GetComponent<TagInputComponent>(quad_entity);
  // auto& cube_velocity_component =
  //     kECManager->GetComponent<VelocityComponent>(quad_entity);

  // if (kPlatform->input_system.IsKeyPressed(KeyCode::kC)) {
  //   cube_transform_component.position.x -=
  //       cube_velocity_component.velocity;  // * delta_time
  // }
}

};  // namespace musashi
