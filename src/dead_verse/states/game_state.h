#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "state.h"

namespace musashi {

class GameState : public State {
  GameState();

  void Tick() override;
  void Update() override;

 private:
  States current_state_;
};

}  // namespace musashi

#endif
