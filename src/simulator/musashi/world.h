#ifndef WORLD_H_
#define WORLD_H_

#include "block.h"
#include "player.h"

#include <memory>
#include <string>

#include "entity/component_manager.h"
#include "renderer/resource_manager.h"
#include "util/log.h"

namespace musashi {

class World {
 public:
  World(Logger* logger, ComponentManager* ec,
        ResourceManager* resource_manager);

  void Init();
  void InitPlayer(const std::string& name);
  template <typename T>
  void InitChunk(EntityBuilder<T>& builder) {
    glm::vec3 current_position = glm::vec3(0.0f, 0.0f, 1.0f);

    TransformComponent transform;
    transform.position = current_position;
    transform.scale = glm::vec3(2.0f, 2.0f, 1.0f);

    QuadComponent quad;
    quad.position = transform.position;
    quad.scale = transform.scale;
    quad.mesh =
        std::make_unique<Mesh<Quad3D::kData.size(), Quad3D::kIndices.size()>>(
            Quad3D::kData, Quad3D::kIndices);

    SpriteComponent sprite;
    sprite.sprite.source =
        resource_manager_->GetTexture(ResourceManager::TextureName::kMinecraft);
    sprite.sprite.data.slot = 0;
    sprite.sprite.data.name = "uTexture";
    sprite.sprite.data.size = {};
    sprite.sprite.data.origin = {};

    AnimationComponent animation;

    auto block = builder.Create("Block");
  }
  void InitTerrain(size_t terrain_size = 10);

 private:
  Logger* logger_;
  ComponentManager* ec_;
  std::unique_ptr<Player> player_;
  ResourceManager* resource_manager_;
  std::unique_ptr<Terrain<5, 5>> terrain_;
};

}  // namespace musashi

#endif
