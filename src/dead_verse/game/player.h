#ifndef PLAYER_H_
#define PLAYER_H_

#include "object.h"

#include <array>
#include <unordered_set>

namespace musashi {

static constexpr uint8_t kMaxPlayerWeapons{2};
static constexpr uint8_t kPrimaryWeaponIdx{0};
static constexpr uint8_t kSecondaryWeaponIdx{1};

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

  void Init() override {
    perks.clear();
    Weapon primary;
    weapons[kPrimaryWeaponIdx] = std::move(primary);
    weapons[kPrimaryWeaponIdx].Init();
  }
  void Destory() override {}
  void HandleInput();
  void Update();
  [[nodiscard]] EntityId GetObjectId() const override { return entity.id; }

  PlayerSettings settings;
  std::unordered_set<Perks> perks;
  std::array<Weapon, kMaxPlayerWeapons> weapons;
};

}  // namespace musashi

#endif
