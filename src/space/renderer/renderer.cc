#include "renderer.h"

#include "entity/components.h"
#include "entity/entity_manager.h"
#include "renderer/resource_manager.h"

namespace musashi {

Renderer::Renderer(Logger& logger, Platform& platform, ComponentManager& ec,
                   ResourceManager& resource_manager)
    : logger_(&logger),
      platform_(&platform),
      ec_(&ec),
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
}

void Renderer::RenderSprite(Shader& program, SpriteComponent& sprite) {
  AttachSprite(program, sprite);
}

void Renderer::Draw(const Entity& entity) {
  bool has_quad{false};
  has_quad = ec_->HasComponent<QuadComponent>(entity.name);
  if (has_quad) {
    auto& quad = ec_->GetComponent<QuadComponent>(entity.name);
    quad.mesh->vertex.Bind();
    quad.mesh->vertex.Draw();
  }
}

bool Renderer::IsDynamicEntity(const Entity& entity) {
  return ec_->HasComponent<AnimationComponent>(entity.name);
}

void Renderer::AttachSprite(Shader& program, SpriteComponent& sprite) {
  sprite.sprite.SetSprite(program);

  auto texture_width = static_cast<float>(sprite.sprite.source->width);
  auto texture_height = static_cast<float>(sprite.sprite.source->height);

  const auto& size = sprite.sprite.data.size;
  const auto& origin = sprite.sprite.data.origin;

  glm::vec2 uv_offset = {(origin.x * size.x) / texture_width,
                         (origin.y * size.y) / texture_height};
  glm::vec2 uv_scale = {size.x / texture_width, size.y / texture_height};

  program.SetVec2("uUvOffset", uv_offset);
  program.SetVec2("uUvScale", uv_scale);
}

void Renderer::ComputeEntityCoordinates(Shader& program,
                                        TransformComponent& transform) {
  const auto& pv = platform_->camera.camera.GetViewProjectionMatrix();

  auto model = glm::mat4(1.0f);
  model = glm::scale(model, transform.scale);
  model = glm::translate(model, transform.position);

  auto mvp = pv * model;

  program.Use();
  program.SetMat4("uMVP", mvp);
}

void Renderer::ShutDown() {
  resource_manager_->ClearResources();
}

void Renderer::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}  // namespace musashi
