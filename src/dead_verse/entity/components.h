#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace musashi {

// Number of unique component type.
static inline constexpr int kNumberOfComponents{6};

enum class ComponentType : uint8_t {
  kTransformComponent = 0,
  kInputComponent = 1,
  kPositionComponent = 2,
  kHealthComponent = 3,
  kCombatComponent = 4,
  kCollisionComponent = 5,
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
  glm::mat4 translate;
  glm::vec3 position;
        glm::vec3 scale;

  static ComponentType Type() { return ComponentType::kTransformComponent; }
};

struct InputComponent : public Component {
  static ComponentType Type() { return ComponentType::kInputComponent; }
};

struct PositionComponent : public Component {
  glm::vec3 position;

  static ComponentType Type() { return ComponentType::kPositionComponent; }
};

struct VelocityComponent {};

struct CameraComponent {};

struct CameraControllerComponent {};

struct TextureComponent {};

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
