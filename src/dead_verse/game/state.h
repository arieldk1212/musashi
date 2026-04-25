#ifndef STATE_H_
#define STATE_H_

#include <cstdint>

namespace musashi {

struct State {
  enum class States : uint8_t {
    kStartState,
    kMenuState,
    kGameActiveState,
    kGameEndState
  };

  States state{States::kGameActiveState};

  void Update(States state);
};

}  // namespace musashi

#endif
