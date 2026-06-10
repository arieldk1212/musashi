#ifndef TIME_H_
#define TIME_H_

#include <chrono>

namespace musashi {

struct Time {
  Time() { Init(); }

  static constexpr float kTickRate{60.0f};        // Updates per second
  static constexpr float kMaxAccumulator{0.25f};  // Lag
  static constexpr float kFixedDeltaTime{1.0f / kTickRate};

  struct Points {
    float last_time{0.0f};
    float delta_time{0.0f};
    float current_time{0.0f};
    float elapsed_time{0.0f};
  };

  static float GetTime() {
    static auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - start;
    return elapsed.count();
  }

  void Init() {
    points.delta_time = 0;
    points.last_time = GetTime();
  }

  [[nodiscard]] float GetCurrentTime() const { return points.current_time; }
  [[nodiscard]] float GetCurrentTimeMs() const {
    return points.current_time * 1000.0f;
  }

  Points points;
};

}  // namespace musashi

#endif
