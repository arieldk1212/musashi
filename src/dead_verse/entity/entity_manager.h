#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include "components.h"

#include <vector>

namespace musashi {

using EntityId = uint32_t;

struct Entity {
  explicit Entity(EntityId);

  EntityId id;
  std::vector<Component> components;

  template <typename Component>
  Component* Get();

  template <typename Component>
  void Add(Component component);
};

}  // namespace musashi

#endif
