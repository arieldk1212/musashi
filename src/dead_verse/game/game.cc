#include "game.h"

namespace musashi {

Game::Game(GameDependencies& dependencies, ResourceManager& resource_manager,
           const GameSpecification& specs)
    : dependencies_(&dependencies),
      resource_manager_(&resource_manager),
      specifications_(specs),
      state_(std::make_unique<State>()) {
  Init();
}

Game::~Game() noexcept {
  Stop();
  glfwTerminate();
}

void Game::Init() {
  glfwInit();
  dependencies_->platform.Init();
  dependencies_->renderer.Init();
  world_ = std::make_shared<World>(&dependencies_->logger, &dependencies_->ec,
                                   resource_manager_);
}

void Game::Run() {
  running_ = true;

  time_.Init();

  while (running_) {
    dependencies_->platform.window->PollEvents();

    dependencies_->platform.camera.Update(time_.points.delta_time,
                                          dependencies_->platform.input_system);

    if (dependencies_->platform.window->ShouldClose()) {
      Stop();
      dependencies_->logger.Critical("PANIC");
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

    dependencies_->renderer.Render(world_);
    dependencies_->physics.Update(world_);

    dependencies_->platform.window->Update();
    musashi::Renderer::Clear();
  }
}

void Game::Update(float ts) {
  // TODO: Play with states here.
  // auto& cube_input_component =
  //     kECManager->GetComponent<TagInputComponent>(quad_entity);
  // auto& cube_velocity_component =
  //     kECManager->GetComponent<VelocityComponent>(quad_entity);
}

};  // namespace musashi
