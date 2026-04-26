#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"

#include <unordered_map>

#include "entity/components.h"
#include "entity/entity_manager.h"

namespace musashi {

class BaseRenderer {
 public:
  virtual ~BaseRenderer() = default;

  virtual void Render() {}
};

struct SpriteRenderer : public BaseRenderer {
  void Render(Shader& shader, SpriteComponent& sprite);
};

class Renderer : public BaseRenderer {
 public:
  Renderer();

  void Init();

  void Render() override;

  void Draw(const Entity& entity);

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
