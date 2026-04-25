#ifndef PLAYER_H_
#define PLAYER_H_

#include "global.h"
#include "object.h"

#include <array>
#include <unordered_set>

#include "entity/component_manager.h"

namespace musashi {

static constexpr uint8_t kMaxPlayerWeapons{2};

enum class Perks : uint8_t { kStamina, kJuggernaut, kNuke, kCount };

struct Weapon : public Object {
  void Init() override {}
  void Destory() override {}
};

struct Projectile : public Object {
  void Init() override {}
  void Destory() override {}
};

struct PlayerSettings {};

struct Player : public Object {
  Entity entity;
  bool destroyed{false};

  // TODO: Set transform at a random location, with base settings
  Player() = default;

  void Init() override {}
  void Destory() override {}
  void HandleInput();
  void Update();
  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }

  PlayerSettings settings;
  std::unordered_set<Perks> perks;
  std::array<Weapon, kMaxPlayerWeapons> weapon;
};

struct PlayerBuilder {
  std::unique_ptr<Player> player;

  PlayerBuilder& Create(const std::string& name) {
    player = std::make_unique<Player>();
    player->entity = kECManager->CreateEntity(name);
    return *this;
  }

  template <IsComponent T>
  PlayerBuilder& WithComponent(T component) {
    kECManager->AddComponent<T>(player->entity.id, std::move(component));
    return *this;
  }

  std::unique_ptr<Player> Build() { return std::move(player); };
};

}  // namespace musashi

#endif
