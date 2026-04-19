#include "global.h"
#include "renderer.h"

#include <glad/glad.h>

#include "entity/component_manager.h"
#include "entity/components.h"
#include "platform/input.h"
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

  auto& camera = kPlatform->camera;

  auto projection = camera.camera.GetProjectionMatrix();
  auto view = camera.camera.GetViewMatrix();
  // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  RenderQuad("Quad3D", projection * view);
  RenderQuad("Quad2D", projection * view);
}

// TODO: Create a view that can iterate thru all the entities with quad
// components instead of giving it names
void Renderer::RenderQuad(const std::string& quad_entity, const glm::mat4& pv) {
  auto& cube_transform_component =
      kECManager->GetComponent<TransformComponent>(quad_entity);
  // auto& cube_input_component =
  //     kECManager->GetComponent<TagInputComponent>(quad_entity);
  // auto& cube_velocity_component =
  //     kECManager->GetComponent<VelocityComponent>(quad_entity);

  // if (kPlatform->input_system.IsKeyPressed(KeyCode::kC)) {
  //   cube_transform_component.position.x -=
  //       cube_velocity_component.velocity;  // * delta_time
  // }

  auto model = glm::mat4(1.0f);
  model = glm::scale(model, cube_transform_component.scale);
  model = glm::translate(model, cube_transform_component.position);

  auto mvp = pv * model;
  Draw(ShaderName::kObjectShader, quad_entity, mvp);
}

void Renderer::Draw(ShaderName shader_name, const std::string& quad_entity,
                    const glm::mat4& mvp) {
  auto& shader = shaders_[shader_name];

  shader->Use();
  shader->SetMat4("uMVP", mvp);

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
  auto unique_shader = std::make_unique<Shader>(vertex_path, fragment_path);
  shaders_[shader_name] = std::move(unique_shader);
}

void Renderer::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}  // namespace musashi
