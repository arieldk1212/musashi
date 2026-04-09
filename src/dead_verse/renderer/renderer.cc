#include "global.h"
#include "renderer.h"

#include "util/log.h"

namespace musashi {

void Renderer::Init() {
  AddShader(ShaderName::kObjectShader, "assets/shaders/object/vert.glsl",
            "assets/shaders/object/frag.glsl");
  kLogger->Trace("RENDERER & SHADERS INITIALIZED");
}

void Renderer::Render() {}

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
}

void Renderer::UseShader(ShaderName shader_name) {
  shaders_[shader_name]->Use();
}

}  // namespace musashi
