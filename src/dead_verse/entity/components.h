#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "platform/input.h"

namespace musashi {

// Number of unique component type.
static inline constexpr int kNumberOfComponents{6};

enum class ComponentType : uint8_t {
  kTransformComponent = 0,
  kInputComponent = 1,
  kVelocityComponent = 2,
  kCollisionComponent = 3,
  kHealthComponent = 4,
  kCombatComponent = 5,
};

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

struct InputComponent : public Component {
  std::vector<KeyCode> keys;

  static ComponentType Type() { return ComponentType::kInputComponent; }
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

struct TextureComponent {};

}  // namespace musashi

#endif
