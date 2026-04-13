#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cstddef>

namespace musashi {

class Game;
class Platform;
class Logger;
class Renderer;
class ComponentManager;

struct Global {
  Global() = default;

  static void Cleanup(Global& global) {
    global.platform = nullptr;
    global.renderer = nullptr;
    global.game = nullptr;
    global.logger = nullptr;
    global.ec_manager = nullptr;
  }

  Game* game;
  Logger* logger;
  Platform* platform;
  Renderer* renderer;
  ComponentManager* ec_manager;
};

extern Global kGlobal;

inline auto& kGame = kGlobal.game;
inline auto& kLogger = kGlobal.logger;
inline auto& kPlatform = kGlobal.platform;
inline auto& kRenderer = kGlobal.renderer;
inline auto& kECManager = kGlobal.ec_manager;

}  // namespace musashi

#endif
