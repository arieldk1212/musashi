#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "application.h"

#include "core/window.h"

namespace musashi {

// TODO: or use dependency injection, think this thru.

struct Global {
  Window* window;
  Application* application;
};

extern Global global;

}  // namespace musashi

#endif