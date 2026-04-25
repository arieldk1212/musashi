#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cstddef>

namespace musashi {

class Game;
class World;
class Logger;
class Renderer;
struct Platform;
struct State;
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
  World* world;
  Logger* logger;
  Platform* platform;
  Renderer* renderer;
  State* state;
  ComponentManager* ec_manager;
};

extern Global kGlobal;

inline auto& kGame = kGlobal.game;
inline auto& kWorld = kGlobal.world;
inline auto& kLogger = kGlobal.logger;
inline auto& kPlatform = kGlobal.platform;
inline auto& kRenderer = kGlobal.renderer;
inline auto& kState = kGlobal.state;
inline auto& kECManager = kGlobal.ec_manager;

}  // namespace musashi

#endif
