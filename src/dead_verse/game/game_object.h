#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

namespace musashi {

class Quad;

class GameObject {
 public:
  virtual ~GameObject() = default;
};

struct GameObjectData {};

class Zombie : public GameObject {
 public:
  // TODO: pos, velocity, size, destroyed..
 private:
};

class Weapon : public GameObject {};

class Bullet : public GameObject {};

class PowerUp : public GameObject {};

}  // namespace musashi

#endif
