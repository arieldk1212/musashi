#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace musashi {

static constexpr int kLogBufferSize{256};

class Application;
class Logger;

// TODO: or use dependency injection, think this thru.

struct Global {
  Global() = default;

  Application* application;
  Logger* logger;
};

extern Global kGlobal;

}  // namespace musashi

#endif
