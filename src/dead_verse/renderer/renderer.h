#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"

#include <memory>

#include "entity/component_manager.h"
#include "game/world.h"
#include "platform/platform.h"
#include "renderer/resource_manager.h"

namespace musashi {

struct SpriteRenderer {
  void Render(Shader& program, SpriteComponent& sprite);
};

class Renderer {
 public:
  explicit Renderer(Logger& logger, Platform& platform, ComponentManager& ec,
                    ResourceManager& resource_manager);

  void Init();

  void Render(std::shared_ptr<World> world);
  void RenderFrame();

  void Draw();  // NOTE: Draw all entities
  void Draw(const Entity& entity);

  void ShutDown();

  static void Clear();

 private:
  Logger* logger_;
  Platform* platform_;
  ComponentManager* ec_;
  ResourceManager* resource_manager_;
  std::unique_ptr<SpriteRenderer> sprite_renderer_;
};

}  // namespace musashi

#endif
