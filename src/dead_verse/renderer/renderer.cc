#include "renderer.h"

namespace musashi {

void Renderer::Update() {}
void Renderer::Render(float ts) {}

void Renderer::ShutDown() {
  for (auto& [_, shader] : shaders_) {
    shader->DeleteProgram();
  }
}

void Renderer::AddShader(std::string shader_name,
                         const std::filesystem::path& vertex_path,
                         const std::filesystem::path& fragment_path) {
  auto unique_shader = std::make_unique<Shader>(vertex_path, fragment_path);
  shaders_[std::move(shader_name)] = std::move(unique_shader);
}

}  // namespace musashi
