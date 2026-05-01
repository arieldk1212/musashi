#include "renderer.h"

#include "renderer/resource_manager.h"

namespace musashi {

void SpriteRenderer::Render(Shader& program, SpriteComponent& sprite) {
  sprite.sprite.SetSprite(program);

  glm::vec2 origin{1, 0};
  glm::vec2 size{126, 126};
  auto texture_width = static_cast<float>(sprite.sprite.source->width);
  auto texture_height = static_cast<float>(sprite.sprite.source->height);

  sprite.sprite.data.size = size;
  sprite.sprite.data.origin = origin;

  glm::vec2 uv_offset = {(origin.x * size.x) / texture_width,
                         (origin.y * size.y) / texture_height};
  glm::vec2 uv_scale = {size.x / texture_width, size.y / texture_height};

  program.SetVec2("uUvOffset", uv_offset);
  program.SetVec2("uUvScale", uv_scale);
}

Renderer::Renderer(Logger& logger, Platform& platform, ComponentManager& ec,
                   ResourceManager& resource_manager)
    : logger_(&logger),
      platform_(&platform),
      ec_(&ec),
      sprite_renderer_(std::make_unique<SpriteRenderer>()),
      resource_manager_(&resource_manager) {}

void Renderer::Init() {
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  resource_manager_->InitResources();
  logger_->Trace("RENDERER & SHADERS INITIALIZED");
}

void Renderer::Render(std::shared_ptr<World> world) {
  auto& program = resource_manager_->GetProgram(
      ResourceManager::ProgramName::kObjectShader);
  program.Use();

  const auto& pv = platform_->camera.camera.GetViewProjectionMatrix();

  for (const auto& zombie : world->GetZombies()) {
    const auto& zombie_entity = zombie.entity;
    if (ec_->HasComponent<TagZombieComponent>(zombie_entity.name)) {
      auto& transform_component =
          ec_->GetComponent<TransformComponent>(zombie_entity.id);

      auto model = glm::mat4(1.0f);
      model = glm::scale(model, transform_component.scale);
      model = glm::translate(model, transform_component.position);
      auto mvp = pv * model;

      program.Use();
      program.SetMat4("uMVP", mvp);

      auto& sprite = ec_->GetComponent<SpriteComponent>(zombie_entity.id);
      sprite_renderer_->Render(program, sprite);

      Draw(zombie_entity);
    }
  }
}

void Renderer::Draw(const Entity& entity) {
  bool has_quad = ec_->HasComponent<QuadComponent>(entity.name);
  if (has_quad) {
    auto& quad = ec_->GetComponent<QuadComponent>(entity.name);
    quad.mesh->vertex.Bind();
    quad.mesh->vertex.Draw();
  }
}

void Renderer::ShutDown() {
  resource_manager_->ClearResources();
}

void Renderer::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}  // namespace musashi
