#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"

#include <memory>

#include "entity/component_manager.h"
#include "musashi/object.h"
#include "musashi/world.h"
#include "platform/platform.h"
#include "renderer/resource_manager.h"

namespace musashi {

class Renderer {
 public:
  explicit Renderer(Logger& logger, Platform& platform, ComponentManager& ec,
                    ResourceManager& resource_manager);

  void Init();

  void RenderFrame();
  void Render(std::shared_ptr<World> world);
  void RenderSprite(Shader& program, SpriteComponent& sprite);
  void RenderAnimation(Shader& program, AnimationComponent& animation,
                       SpriteComponent& sprite, std::string_view type);

  void Draw();
  void Draw(const Entity& entity);

  bool IsDynamicEntity(const Entity& entity);
  void AttachSprite(Shader& program, SpriteComponent& sprite);
  void ComputeEntityCoordinates(Shader& program, TransformComponent& transform);

  void ShutDown();

  static void Clear();

 private:
  Logger* logger_;
  Platform* platform_;
  ComponentManager* ec_;
  ResourceManager* resource_manager_;
  std::unique_ptr<Animations> animations_;
};

}  // namespace musashi

#endif
