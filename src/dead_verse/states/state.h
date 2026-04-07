#ifndef STATE_H_
#define STATE_H_

#include <cstdint>

namespace musashi {

enum class States : uint8_t {
  kStateMenu,
  kStateGame,
};

class State {
 public:
  virtual ~State() = default;

  void Tick();
  virtual void Update() = 0;
};

}  // namespace musashi

#endif
