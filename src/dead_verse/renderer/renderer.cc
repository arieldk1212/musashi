#include "global.h"
#include "renderer.h"
#include "shader.h"

#include <glad/glad.h>

#include "entity/component_manager.h"
#include "entity/components.h"
#include "game/world.h"
#include "platform/platform.h"
#include "util/log.h"

namespace musashi {

void SpriteRenderer::Render(Shader& shader, SpriteComponent& sprite) {
  sprite.sprite.SetSprite(shader);

  glm::vec2 origin{1, 0};
  glm::vec2 size{126, 126};
  auto texture_width = static_cast<float>(sprite.sprite.source->width);
  auto texture_height = static_cast<float>(sprite.sprite.source->height);

  sprite.sprite.data.size = size;
  sprite.sprite.data.origin = origin;

  glm::vec2 uv_offset = {(origin.x * size.x) / texture_width,
                         (origin.y * size.y) / texture_height};
  glm::vec2 uv_scale = {size.x / texture_width, size.y / texture_height};

  shader.SetVec2("uUvOffset", uv_offset);
  shader.SetVec2("uUvScale", uv_scale);
}

Renderer::Renderer()
    : sprite_renderer_(std::make_unique<SpriteRenderer>()) {}

void Renderer::Init() {
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  AddShader(ShaderName::kObjectShader, "assets/shaders/object/vert.glsl",
            "assets/shaders/object/frag.glsl");
  UseShader(ShaderName::kObjectShader);
  kLogger->Trace("RENDERER & SHADERS INITIALIZED");
}

void Renderer::Render() {
  auto& shader = shaders_[ShaderName::kObjectShader];
  shader->Use();

  const auto& pv = kPlatform->camera.camera.GetViewProjectionMatrix();

  for (const auto& entity : kWorld->GetWorldEntities()) {
    auto& transform_component =
        kECManager->GetComponent<TransformComponent>(entity.id);

    auto model = glm::mat4(1.0f);
    model = glm::scale(model, transform_component.scale);
    model = glm::translate(model, transform_component.position);
    auto mvp = pv * model;

    shader->Use();
    shader->SetMat4("uMVP", mvp);

    auto& sprite = kECManager->GetComponent<SpriteComponent>(entity.id);
    sprite_renderer_->Render(*shader, sprite);

    Draw(entity);
  }
}

void Renderer::Draw(const Entity& entity) {
  bool has_quad = kECManager->HasComponent<QuadComponent>(entity.name);
  auto& quad = kECManager->GetComponent<QuadComponent>(entity.name);
  quad.mesh->vertex.Bind();
  quad.mesh->vertex.Draw();
}

void Renderer::ShutDown() {
  for (auto& [_, shader] : shaders_) {
    shader->DeleteProgram();
  }
}

void Renderer::UseShader(ShaderName shader_name) {
  shaders_[shader_name]->Use();
}

void Renderer::AddShader(ShaderName shader_name,
                         const std::filesystem::path& vertex_path,
                         const std::filesystem::path& fragment_path) {
  auto shader = std::make_unique<Shader>(vertex_path, fragment_path);
  shaders_[shader_name] = std::move(shader);
}

void Renderer::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}  // namespace musashi
