#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <cstdint>

namespace musashi {

enum class States : uint8_t { kMenuState, kGameActiveState, kGameEndState };

class State {
 public:
  virtual ~State() = default;

  virtual void Update() = 0;
  [[nodiscard]] virtual States GetState() const = 0;
};

class GameState : public State {
 public:
  GameState() = default;

  void Update() override {}

  [[nodiscard]] States GetState() const override { return current_state_; }

 private:
  States current_state_{States::kGameActiveState};
};

}  // namespace musashi

#endif
