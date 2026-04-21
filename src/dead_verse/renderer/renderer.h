#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"

#include <unordered_map>

namespace musashi {

struct SpriteRenderer {
  void Render();
};

class Renderer {
 public:
  Renderer() = default;

  void Init();
  void Render();
  void RenderQuad(ShaderName shader_name, const std::string& quad_entity,
                  const glm::mat4& pv);
  void RenderSprite();
  void RenderGameObject();
  void Draw(const std::string& quad_entity);
  void ShutDown();

  void AddShader(ShaderName shader_name,
                 const std::filesystem::path& vertex_path,
                 const std::filesystem::path& fragment_path);
  void UseShader(ShaderName shader_name);

  static void Clear();

 private:
  std::unique_ptr<SpriteRenderer> sprite_renderer_;
  std::unordered_map<ShaderName, std::unique_ptr<Shader>> shaders_;
};

}  // namespace musashi

#endif
