#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"

#include <unordered_map>

namespace musashi {

class Renderer {
 public:
  Renderer() = default;

  void Init();
  void Render();
  void RenderQuad(const std::string& quad_entity, const glm::mat4& pv);
  void Draw(ShaderName shader_name, const std::string& quad_entity,
            const glm::mat4& mvp);
  void ShutDown();

  void AddShader(ShaderName shader_name,
                 const std::filesystem::path& vertex_path,
                 const std::filesystem::path& fragment_path);
  void UseShader(ShaderName shader_name);

  static void Clear();

 private:
  std::unordered_map<ShaderName, std::unique_ptr<Shader>> shaders_;
};

}  // namespace musashi

#endif
