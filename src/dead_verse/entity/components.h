#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace musashi {

// Number of unique component type.
static inline constexpr int kNumberOfComponents{5};

enum class ComponentType : uint8_t {
  kHealthComponent = 0,
  kCombatComponent = 1,
  kCollisionComponent = 2,
  kPositionComponent = 3,
  kTransformComponent = 4
};

template <typename T>
concept IsComponent = requires {
  { T::Type() } -> std::same_as<ComponentType>;
};

struct PositionComponent {
  static ComponentType Type() { return ComponentType::kPositionComponent; }
};

struct TransformComponent {
  glm::mat4 translate;
  glm::vec3 position;
  glm::vec3 scale;
  static ComponentType Type() { return ComponentType::kTransformComponent; }
};

struct CollisionComponent {
  static ComponentType Type() { return ComponentType::kCollisionComponent; }
};

struct HealthComponent {
  static ComponentType Type() { return ComponentType::kHealthComponent; }
};

struct CombatComponent {
  static ComponentType Type() { return ComponentType::kCombatComponent; }
};

}  // namespace musashi

#endif
