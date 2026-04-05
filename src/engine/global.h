#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace musashi {

class Input;
class Logger;
class Renderer;
class Application;

struct Global {
  Global() = default;

  static void Cleanup(Global& global) {
    global.application = nullptr;
    global.logger = nullptr;
    global.renderer = nullptr;
    global.input = nullptr;
  }

  Input* input;
  Logger* logger;
  Renderer* renderer;
  Application* application;
};

extern Global kGlobal;

}  // namespace musashi

#endif
