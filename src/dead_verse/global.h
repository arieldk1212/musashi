#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cstddef>

namespace musashi {

class Game;
class Logger;
class Renderer;
struct Platform;
class GameState;
class ComponentManager;

struct Global {
  Global() = default;

  static void Cleanup(Global& global) {
    global.ec_manager = nullptr;
    global.renderer = nullptr;
    global.game = nullptr;
    global.platform = nullptr;
    global.state = nullptr;
    global.logger = nullptr;
  }

  Game* game;
  Logger* logger;
  Platform* platform;
  Renderer* renderer;
  GameState* state;
  ComponentManager* ec_manager;
};

extern Global kGlobal;

inline auto& kGame = kGlobal.game;
inline auto& kLogger = kGlobal.logger;
inline auto& kPlatform = kGlobal.platform;
inline auto& kRenderer = kGlobal.renderer;
inline auto& kState = kGlobal.state;
inline auto& kECManager = kGlobal.ec_manager;

}  // namespace musashi

#endif
