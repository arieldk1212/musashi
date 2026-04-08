#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <string>

#include "platform/window.h"

namespace musashi {

struct GameSpecification {
  std::string game_name = "Dead Verse";
  WindowSpecification window_specs;
};

class Game {
 public:
  static constexpr int kMaxFrameSkip{5};
  static constexpr int kTicksPerSecond{25};
  static constexpr int kSkipTicks{1000 / kTicksPerSecond};

  Game();
  explicit Game(const GameSpecification& specs = GameSpecification());
  ~Game() noexcept;

  void Run();
  void Stop() { running_ = false; }
  void Update();
  void Tick();

 private:
  bool running_{false};
  std::shared_ptr<Window> window_;
  GameSpecification specifications_;
};

}  // namespace musashi

// inline float delta_time{0.0f};
// inline float last_frame{0.0f};

#endif
