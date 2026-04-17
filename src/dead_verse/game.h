#ifndef GAME_H_
#define GAME_H_

#include <string>

#include "platform/window.h"
#include "util/time.h"

namespace musashi {

struct GameSpecification {
  std::string game_name = "Dead Verse";
  WindowSpecification window_specs;
};

class Game {
 public:
  Game();
  explicit Game(const GameSpecification& specs = GameSpecification());
  ~Game() noexcept;

  void Init();
  void Run();
  void Stop() { running_ = false; }
  void Update(float ts = 0);
  void TestEntity();

 private:
  Time time_;
  bool running_{false};
  GameSpecification specifications_;
};

}  // namespace musashi

#endif
