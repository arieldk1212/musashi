#include "global.h"
#include "renderer.h"

#include <glad/glad.h>

#include "entity/component_manager.h"
#include "entity/components.h"
#include "platform/platform.h"
#include "util/log.h"

namespace musashi {

void Renderer::Init() {
  glEnable(GL_DEPTH_TEST);

  AddShader(ShaderName::kObjectShader, "assets/shaders/object/vert.glsl",
            "assets/shaders/object/frag.glsl");
  UseShader(ShaderName::kObjectShader);
  kLogger->Trace("RENDERER & SHADERS INITIALIZED");
}

void Renderer::Render() {
  Clear();

  RenderQuad(ShaderName::kObjectShader, "Quad3D",
             kPlatform->camera.camera.GetViewProjectionMatrix());
  RenderQuad(ShaderName::kObjectShader, "Quad2D",
             kPlatform->camera.camera.GetViewProjectionMatrix());
}

// TODO: Create a view that can iterate thru all the entities with quad
// components instead of giving it names
void Renderer::RenderQuad(ShaderName shader_name,
                          const std::string& quad_entity, const glm::mat4& pv) {
  auto& cube_transform_component =
      kECManager->GetComponent<TransformComponent>(quad_entity);

  auto model = glm::mat4(1.0f);
  model = glm::scale(model, cube_transform_component.scale);
  model = glm::translate(model, cube_transform_component.position);

  auto mvp = pv * model;

  auto& shader = shaders_[shader_name];

  shader->Use();
  shader->SetMat4("uMVP", mvp);

  auto& sprite = kECManager->GetComponent<SpriteComponent>(quad_entity);
  shader->SetInt(sprite.sprite.data.name, sprite.sprite.data.slot);
  sprite.sprite.source->Bind(sprite.sprite.data.slot);

  Draw(quad_entity);
}

void Renderer::Draw(const std::string& quad_entity) {
  auto& quad = kECManager->GetComponent<QuadComponent>(quad_entity);
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
