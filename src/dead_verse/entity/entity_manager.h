#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <cstdint>
#include <limits>
#include <string>

namespace musashi {

using EntityId = uint32_t;
static inline constexpr int kMaxEntities{5000};
static inline constexpr EntityId kNullEntity =
    std::numeric_limits<EntityId>::max();

struct Entity {
  explicit Entity(EntityId id, std::string entity_name)
      : entity_name(std::move(entity_name)),
        id(id) {}
  std::string entity_name;
  EntityId id;
};

}  // namespace musashi

#endif
