#include "global.h"
#include "renderer.h"

#include <glad/glad.h>

#include "platform/platform.h"
#include "util/log.h"
#include "util/time.h"

namespace musashi {

void Renderer::Init() {
  glEnable(GL_DEPTH_TEST);
  AddShader(ShaderName::kObjectShader, "assets/shaders/object/vert.glsl",
            "assets/shaders/object/frag.glsl");
  kLogger->Trace("RENDERER & SHADERS INITIALIZED");
  UseShader(ShaderName::kObjectShader);

  CreateCube();
}

void Renderer::Render() {
  Clear();

  auto& camera = kPlatform->camera;
  auto projection = camera.camera.GetProjectionMatrix();
  auto view = camera.camera.GetViewMatrix();

  auto model = glm::mat4(1.0f);
  model = glm::rotate(model, Time::GetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
  model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  auto mvp = projection * view * model;

  Draw(ShaderName::kObjectShader, VertexName::kCube, mvp);
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

void Renderer::CreateCube() {
  std::vector<Vertex> data = {
      // Front face
      {{-0.5f, -0.5f, 0.5f}},  // 0: Bottom Left
      {{0.5f, -0.5f, 0.5f}},   // 1: Bottom Right
      {{0.5f, 0.5f, 0.5f}},    // 2: Top Right
      {{-0.5f, 0.5f, 0.5f}},   // 3: Top Left

      // Back face
      {{-0.5f, -0.5f, -0.5f}},  // 4: Bottom Left
      {{0.5f, -0.5f, -0.5f}},   // 5: Bottom Right
      {{0.5f, 0.5f, -0.5f}},    // 6: Top Right
      {{-0.5f, 0.5f, -0.5f}}    // 7: Top Left
  };
  std::vector<uint32_t> indices = {// Front
                                   0, 1, 2, 2, 3, 0,
                                   // Right
                                   1, 5, 6, 6, 2, 1,
                                   // Back
                                   5, 4, 7, 7, 6, 5,
                                   // Left
                                   4, 0, 3, 3, 7, 4,
                                   // Top
                                   3, 2, 6, 6, 7, 3,
                                   // Bottom
                                   4, 5, 1, 1, 0, 4};

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

}  // namespace musashi
