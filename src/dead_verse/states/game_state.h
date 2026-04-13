#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "state.h"

#include "util/time.h"

namespace musashi {

class GameState : public State {
 public:
  GameState();

  int Tick();
  void Update() override;

 private:
  Time time_;
  States current_state_;
};

}  // namespace musashi

#endif
