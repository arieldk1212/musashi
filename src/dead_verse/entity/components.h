#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "renderer/mesh.h"
#include "renderer/sprite.h"

namespace musashi {

enum class ComponentType : uint8_t {
  kTransformComponent = 0,
  kInputComponent = 1,
  kVelocityComponent = 2,
  kCollisionComponent = 3,
  kHealthComponent = 4,
  kCombatComponent = 5,
  kTextureComponent = 6,
  kSpriteComponent = 7,
  kQuadComponent = 8,
  kAnimationComponent = 9,
  kZombieComponent = 10,
};

// Number of unique component type.
static inline constexpr int kNumberOfComponents{11};

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

struct TextureComponent : public Component {
  std::unique_ptr<Texture> source;
  std::string name;
  uint32_t slot;

  static ComponentType Type() { return ComponentType::kTextureComponent; };
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
  static ComponentType Type() { return ComponentType::kAnimationComponent; }
};

struct TagInputComponent : public Component {
  static ComponentType Type() { return ComponentType::kInputComponent; }
};

struct TagZombieComponent : public Component {
  static ComponentType Type() { return ComponentType::kZombieComponent; }
};

}  // namespace musashi

#endif
