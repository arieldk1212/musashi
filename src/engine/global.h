#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace musashi {
class Application;

// TODO: or use dependency injection, think this thru.

struct Global {
  Global() = default;
  Application* application;
};

extern Global kGlobal;

}  // namespace musashi

#endif