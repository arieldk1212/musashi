#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

namespace musashi {

struct Entity {
  virtual ~Entity() = default;

  void Tick();
};

class EntityManager {
 public:
 private:
};

}  // namespace musashi

#endif
