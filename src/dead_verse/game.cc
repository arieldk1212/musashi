#include "game.h"
#include "global.h"

#include "entity/component_manager.h"
#include "entity/components.h"
#include "platform/platform.h"
#include "renderer/renderer.h"
#include "util/log.h"
#include "util/time.h"

namespace musashi {

Game::Game(const GameSpecification& specs) {
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
    time_.points.elapsed_time =
        time_.points.current_time - time_.points.last_time;

    time_.points.last_time = time_.points.current_time;
    time_.points.accumulator += time_.points.elapsed_time;

    Update(time_.points.elapsed_time);

    while (time_.points.accumulator >= Time::kFixedDeltaTime) {
      Update(Time::kFixedDeltaTime);
      time_.points.accumulator -= Time::kFixedDeltaTime;
    }

    kRenderer->Render();

    kPlatform->window->Update();
    kPlatform->Clear();
  }
}

void Game::Update(float ts) {
  kPlatform->Update(ts);
}

};  // namespace musashi
