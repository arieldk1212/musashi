#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace musashi {

class Input;
class Logger;
class Renderer;
class Game;

struct Global {
  Global() = default;

  static void Cleanup(Global& global) {
    global.input = nullptr;
    global.renderer = nullptr;
    global.game = nullptr;
    global.logger = nullptr;
  }

  Input* input;
  Logger* logger;
  Renderer* renderer;
  Game* game;
};

extern Global kGlobal;

}  // namespace musashi

#endif
