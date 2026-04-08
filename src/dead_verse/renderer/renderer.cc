#include "global.h"
#include "renderer.h"

#include "util/log.h"

namespace musashi {

void Renderer::Update() {}
void Renderer::Render(float ts) {}

void Renderer::ShutDown() {
  for (auto& [_, shader] : shaders_) {
    shader->DeleteProgram();
  }
}

void Renderer::AddShader(ShaderName shader_name,
                         const std::filesystem::path& vertex_path,
                         const std::filesystem::path& fragment_path) {
  auto unique_shader = std::make_unique<Shader>(vertex_path, fragment_path);
  shaders_[shader_name] = std::move(unique_shader);
  kGlobal.logger->Debug("Shader Created");
}

void Renderer::UseShader(ShaderName shader_name) {
  shaders_[shader_name]->Use();
}

}  // namespace musashi
