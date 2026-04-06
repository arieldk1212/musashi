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
  Game();
  explicit Game(const GameSpecification& specs = GameSpecification());
  ~Game() noexcept;

  void Run();
  void Stop() { running_ = false; }

 private:
  bool running_{false};
  std::shared_ptr<Window> window_;
  GameSpecification specifications_;
};

}  // namespace musashi

// inline float delta_time{0.0f};
// inline float last_frame{0.0f};
//
//   void Run();
//   void Shaders();

//  private:
//   GLuint VAO_{0};
//   GLuint VBO_{0};
//   GLuint LightVAO_{0};
//   std::string game_title_;
//   std::unique_ptr<Camera> camera_;
//   std::unique_ptr<Shader> shader_;
//   // std::unique_ptr<Texture> texture_;
//   std::unique_ptr<Shader> light_shader_;
// };

#endif
