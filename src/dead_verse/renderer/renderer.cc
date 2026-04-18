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
  kLogger->Trace("RENDERER & SHADERS INITIALIZED");
  UseShader(ShaderName::kObjectShader);

  InitCubeMesh();
}

void Renderer::Render() {
  Clear();

  auto& camera = kPlatform->camera;

  auto projection = camera.camera.GetProjectionMatrix();
  auto view = camera.camera.GetViewMatrix();
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  RenderTestEntity(projection * view);
}

void Renderer::ShutDown() {
  for (auto& [_, shader] : shaders_) {
    shader->DeleteProgram();
  }
}

void Renderer::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(ShaderName shader_name, VertexName name,
                    const glm::mat4& mvp) {
  auto& shader = shaders_[shader_name];

  shader->Use();
  shader->SetMat4("uMVP", mvp);

  vertex_buffers_[name]->Bind();
  vertex_buffers_[name]->Draw();
}

void Renderer::InitCubeMesh() {
  std::vector<Vertex> data = {{{-0.5f, -0.5f, 0.5f}},  {{0.5f, -0.5f, 0.5f}},
                              {{0.5f, 0.5f, 0.5f}},    {{-0.5f, 0.5f, 0.5f}},
                              {{-0.5f, -0.5f, -0.5f}}, {{0.5f, -0.5f, -0.5f}},
                              {{0.5f, 0.5f, -0.5f}},   {{-0.5f, 0.5f, -0.5f}}};
  std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1,
                                   5, 4, 7, 7, 6, 5, 4, 0, 3, 3, 7, 4,
                                   3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4};

  auto cube = std::make_unique<VertexBuffer>();
  cube->Init(data, indices);
  vertex_buffers_[VertexName::kCube] = std::move(cube);
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

void Renderer::RenderTestEntity(const glm::mat4& pv) {
  auto& cube_component = kECManager->GetComponent<TransformComponent>("Cube");
  auto& cube_input_component =
      kECManager->GetComponent<TagInputComponent>("Cube");
  auto& cube_velocity_component =
      kECManager->GetComponent<VelocityComponent>("Cube");

  if (kPlatform->input_system.IsKeyPressed(KeyCode::kC)) {
    cube_component.position.x -= cube_velocity_component.velocity;
  }

  auto model = glm::mat4(1.0f);
  model = glm::scale(model, cube_component.scale);
  model = glm::translate(model, cube_component.position);

  auto mvp = pv * model;
  Draw(ShaderName::kObjectShader, VertexName::kCube, mvp);
}

}  // namespace musashi
