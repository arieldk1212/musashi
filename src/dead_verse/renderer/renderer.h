#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"
#include "texture.h"

#include <string>
#include <unordered_map>

#include "platform/opengl/vertex_buffer.h"

namespace musashi {

enum class ShaderName : uint8_t { kObjectShader };

class Renderer {
 public:
  Renderer() = default;

  void Init();

  void Render();
  void RenderCube();

  void AddShader(ShaderName shader_name,
                 const std::filesystem::path& vertex_path,
                 const std::filesystem::path& fragment_path);
  void UseShader(ShaderName shader_name);

  void ShutDown();

 private:
  std::unordered_map<std::string, Texture> textures_;
  std::unordered_map<ShaderName, std::unique_ptr<Shader>> shaders_;
  std::unordered_map<std::string, std::unique_ptr<VertexBuffer>>
      vertex_buffers_;
};

}  // namespace musashi

#endif
