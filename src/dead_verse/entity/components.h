#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <type_traits>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace musashi {

enum class ComponentType : uint8_t {
  kHealthComponent = 0,
  kCombatComponent = 1,
  kCollisionComponent = 2,
  kPositionComponent = 3,
  kTransformComponent = 4
};

static inline constexpr int kNumberOfComponents{5};

struct Component {
  virtual ~Component() = default;

  virtual ComponentType Type() = 0;
};

template <typename T>
concept IsComponent = std::is_base_of_v<Component, T>;

struct PositionComponent : public Component {
  ComponentType Type() override { return ComponentType::kPositionComponent; }
};

struct TransformComponent : public Component {
  glm::mat4 translate;
  glm::vec3 position;
  glm::vec3 scale;

  ComponentType Type() override { return ComponentType::kTransformComponent; }
};

struct CollisionComponent : public Component {
  ComponentType Type() override { return ComponentType::kCollisionComponent; }
};

struct HealthComponent : public Component {
  ComponentType Type() override { return ComponentType::kHealthComponent; }
};

struct CombatComponent : public Component {
  ComponentType Type() override { return ComponentType::kCombatComponent; }
};

}  // namespace musashi

#endif
