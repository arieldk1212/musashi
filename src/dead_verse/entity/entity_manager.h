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
      : id(id),
        name(std::move(entity_name)) {}

        void Destroy() { id = kNullEntity; }
  [[nodiscard]] bool IsDestroyed() const { return id == kNullEntity; }

  EntityId id;
  std::string name;
};

}  // namespace musashi

#endif
