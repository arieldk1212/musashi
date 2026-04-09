#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace musashi {

struct Component {
  virtual ~Component() = default;

  virtual void Init() {};
};

struct PositionComponent : public Component {};

struct TransformComponent : public Component {
  glm::mat4 translate;
  glm::vec3 position;
  glm::vec3 scale;
};

struct CollisionComponent : public Component {};

struct HealthComponent : public Component {};

struct CombatComponent : public Component {};

}  // namespace musashi

#endif
