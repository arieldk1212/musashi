#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include "entity_manager.h"

#include <atomic>
#include <cstdint>
#include <memory>

namespace musashi {

inline constexpr int kMaxComponents{500};

// TODO: Define sparse set & pool.
// TODO: System via lambdas, how to check events?

template <typename Size>
struct ComponentPool {};

struct ComponentRegistry {
  static constexpr EntityId kBaseEntity{0};

  static EntityId GenerateEntityId() {
    static std::atomic<EntityId> next{kBaseEntity + 1};
    return next.fetch_add(1);
  }
};

template <size_t Size>
class ComponentManager {
 public:
  ComponentManager() = default;

  Entity CreateEntity() {
    return Entity{ComponentRegistry::GenerateEntityId()};
  }

  template <typename Component>
  void Add(EntityId id);
  void View();

 private:
  size_t max_size_{kMaxComponents};
  // std::unique_ptr<ComponentPool> pool_;
};

}  // namespace musashi

#endif
