#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/vec2.hpp>

namespace musashi {

class GameObject {
 public:
  virtual ~GameObject() = default;
};

struct GameObjectData {};

struct Zombie : public GameObject {
  glm::vec2 scale;
  glm::vec2 position;
  glm::vec2 velocity;
  bool destroyed{false};

  void Create();
  void Destory();
  void Transform();
};


class Weapon : public GameObject {};

class Bullet : public GameObject {
    void CheckHit();
};

class Perks : public GameObject {
    void Destory();
};

struct Player : public GameObject {
    Perks perks;
    Weapon weapon;
};

}  // namespace musashi

#endif
