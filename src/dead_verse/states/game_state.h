#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "state.h"

namespace musashi {

class GameState : public State {
  GameState();

  void Tick();
  void Update();
  void Render();

 private:
};

}  // namespace musashi

#endif
