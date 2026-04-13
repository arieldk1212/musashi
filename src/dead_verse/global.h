#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cstddef>

namespace musashi {

class Game;
class Input;
class Logger;
class Renderer;
class ComponentManager;

struct Global {
  Global() = default;

  static void Cleanup(Global& global) {
    global.input = nullptr;
    global.renderer = nullptr;
    global.game = nullptr;
    global.logger = nullptr;
    global.ec_manager = nullptr;
  }

  Game* game;
  Input* input;
  Logger* logger;
  Renderer* renderer;
  ComponentManager* ec_manager;
};

extern Global kGlobal;

inline auto& kGame = kGlobal.game;
inline auto& kInput = kGlobal.input;
inline auto& kLogger = kGlobal.logger;
inline auto& kRenderer = kGlobal.renderer;
inline auto& kECManager = kGlobal.ec_manager;

}  // namespace musashi

#endif
