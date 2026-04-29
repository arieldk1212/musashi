#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"

#include <memory>
#include <unordered_map>

#include "entity/component_manager.h"
#include "game/world.h"
#include "platform/platform.h"

namespace musashi {

struct SpriteRenderer {
  void Render(Shader& program, SpriteComponent& sprite);
};

class Renderer {
 public:
  explicit Renderer(Logger& logger, Platform& platform, ComponentManager& ec);

  void Init();

  void Render(std::shared_ptr<World> world);

  void Draw(const Entity& entity);

  void ShutDown();

  void AddProgram(ShaderName shader_name,
                  const std::filesystem::path& vertex_path,
                  const std::filesystem::path& fragment_path);
  void UseProgram(ShaderName shader_name);

  static void Clear();

 private:
  Logger* logger_;
  Platform* platform_;
  ComponentManager* ec_;
  std::unique_ptr<SpriteRenderer> sprite_renderer_;
  std::unordered_map<ShaderName, std::unique_ptr<Shader>> programs_;
};

}  // namespace musashi

#endif
