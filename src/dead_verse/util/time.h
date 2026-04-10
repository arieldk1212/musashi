#ifndef TIME_H_
#define TIME_H_

#include <GLFW/glfw3.h>

namespace musashi {

struct Time {
  static float GetTime() { return static_cast<float>(glfwGetTime()); }
};

}  // namespace musashi

#endif
