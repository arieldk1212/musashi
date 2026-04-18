#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"

#include <unordered_map>

#include "platform/opengl/vertex_buffer.h"

namespace musashi {

enum class VertexName : uint8_t { kCube };
enum class ShaderName : uint8_t { kObjectShader };

class Renderer {
 public:
  Renderer() = default;

  void Init();
  void Render();
  void ShutDown();
  void Draw(ShaderName shader_name, VertexName name, const glm::mat4& mvp);

  void InitCubeMesh();
  void RenderTestEntity(const glm::mat4& pv);

  void AddShader(ShaderName shader_name,
                 const std::filesystem::path& vertex_path,
                 const std::filesystem::path& fragment_path);
  void UseShader(ShaderName shader_name);

  static void Clear();

 private:
  std::unordered_map<ShaderName, std::unique_ptr<Shader>> shaders_;
  std::unordered_map<VertexName, std::unique_ptr<VertexBuffer>> vertex_buffers_;
};

}  // namespace musashi

#endif
