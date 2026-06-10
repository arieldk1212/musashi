#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include "entity_manager.h"

#include <atomic>
#include <stdexcept>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "musashi/object.h"
#include "renderer/mesh.h"
#include "renderer/sprite.h"

namespace musashi {

enum class ComponentType : uint8_t {
  kTransformComponent,
  kInputComponent,
  kVelocityComponent,
  kCollisionComponent,
  kHealthComponent,
  kCombatComponent,
  kSpriteComponent,
  kQuadComponent,
  kAnimationComponent,
  kZombieComponent,
  kCount
};

static inline constexpr int kNumberOfComponents =
    static_cast<int>(ComponentType::kCount);

struct Component {
  virtual ~Component() = default;
};

template <typename T>
concept HasComponentType = requires {
  { T::Type() } -> std::same_as<ComponentType>;
};

template <typename T>
concept HasComponentBase = std::derived_from<T, Component>;

template <typename T>
concept IsComponent = HasComponentType<T> && HasComponentBase<T>;

struct TransformComponent : public Component {
  glm::vec3 position{0.0f};
  glm::vec3 scale{0.0f};

  static ComponentType Type() { return ComponentType::kTransformComponent; }
};

struct VelocityComponent : public Component {
  float velocity{0.0f};

  explicit VelocityComponent(float velocity)
      : velocity(velocity) {}

  static ComponentType Type() { return ComponentType::kVelocityComponent; }
};

struct CollisionComponent : public Component {
  static ComponentType Type() { return ComponentType::kCollisionComponent; }
};

struct HealthComponent : public Component {
  static ComponentType Type() { return ComponentType::kHealthComponent; }
};

struct CombatComponent : public Component {
  static ComponentType Type() { return ComponentType::kCombatComponent; }
};

struct SpriteComponent : public Component {
  Sprite sprite;

  static ComponentType Type() { return ComponentType::kSpriteComponent; };
};

struct QuadComponent : public Component {
  glm::vec3 position;
  glm::vec3 scale;
  glm::vec3 color;
  std::unique_ptr<Mesh> mesh{nullptr};

  static ComponentType Type() { return ComponentType::kQuadComponent; };
};

struct AnimationComponent : public Component {
  int current_frame{0};
  ObjectAnimation current_animation;
  static ComponentType Type() { return ComponentType::kAnimationComponent; }
};

struct TagInputComponent : public Component {
  static ComponentType Type() { return ComponentType::kInputComponent; }
};

struct TagZombieComponent : public Component {
  static ComponentType Type() { return ComponentType::kZombieComponent; }
};

struct EntityRegistry {
  static constexpr EntityId kBaseEntity{0};

  static std::optional<EntityId> GenerateEntityId() {
    static std::atomic<EntityId> next{kBaseEntity + 1};
    if (next == kMaxEntities) {
      throw std::runtime_error("Reached Entity Capacity");
      return std::nullopt;
    }
    return next.fetch_add(1);
  }
};

}  // namespace musashi

#endif
