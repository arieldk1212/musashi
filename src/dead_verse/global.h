#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace musashi {

class Input;
class Logger;
class Renderer;
class Game;
class GameState;

struct Global {
  Global() = default;

  static void Cleanup(Global& global) {
    global.input = nullptr;
    global.renderer = nullptr;
    global.state = nullptr;
    global.game = nullptr;
    global.logger = nullptr;
  }

  Game* game;
  Input* input;
  Logger* logger;
  GameState* state;
  Renderer* renderer;
};

extern Global kGlobal;

}  // namespace musashi

#endif
