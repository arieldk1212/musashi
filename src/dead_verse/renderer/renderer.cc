#include "renderer.h"
#include "shader.h"

namespace musashi {

Renderer::ShaderID Renderer::CreateGraphicsShader(
    const std::filesystem::path& vertex_shader,
    const std::filesystem::path& fragment_shader) {
  Shader shaders(vertex_shader, fragment_shader);
}

void Renderer::Update() {}
void Renderer::Render() {}

}  // namespace musashi
