#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "global.h"
#include "object.h"

#include "entity/component_manager.h"
#include "entity/entity_manager.h"

namespace musashi {

static constexpr std::vector<std::pair<int, int>> kZombieSpawnLocations;

struct Zombie : public Object {
  Entity entity;
  bool destroyed{false};

  // TODO: Set transform at a random location
  Zombie() = default;

  void Init() override {}
  void Destory() override {}
  void Create();
  void Transform();

  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }
};

struct ZombieBuilder {
  Zombie zombie;

  ZombieBuilder& Create(const std::string& name) {
    zombie.entity = kECManager->CreateEntity(name);
    return *this;
  }

  template <IsComponent T>
  ZombieBuilder& WithComponent(T component) {
    kECManager->AddComponent<T>(zombie.entity.id, std::move(component));
  }

  Zombie Build() {
    Zombie complete = zombie;
    zombie = Zombie();
    return complete;
  };
};

}  // namespace musashi

#endif
