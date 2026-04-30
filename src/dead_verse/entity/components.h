#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include "entity_manager.h"

#include <unordered_map>

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
  kSpriteComponent = 6,
  kQuadComponent = 7,
  kAnimationComponent = 8,
  kZombieComponent = 9,
};

// Number of unique component type.
static inline constexpr int kNumberOfComponents{10};

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
      return std::nullopt;
    }
    return next.fetch_add(1);
  }
};

class ComponentRegistry {
 public:
  ComponentRegistry() = default;

  template <IsComponent T>
  void Register(std::string name, ComponentType type,
                std::function<void(T)> register_method) {
    register_method();
    IncrementSize();
    components_[std::move(name)] = GetComponentsSize();
  }

  [[nodiscard]] static int GetComponentsSize() { return kCurrentSize; }

 private:
  static void IncrementSize() {
    static std::atomic<int> size{kCurrentSize + 1};
    size.fetch_add(1);
  }

  static constexpr int kCurrentSize{0};

  std::unordered_map<std::string, uint8_t> components_;
};

}  // namespace musashi

#endif
