#ifndef MUSASHI_INCLUDE_GAME_WINDOW_H_
#define MUSASHI_INCLUDE_GAME_WINDOW_H_

#include <raylib.h>
#include <string>

namespace game {

constexpr int kGameWidth = 800;
constexpr int kGameHeight = 450;

class Game {
public:
  Game(const std::string &window_title);
  ~Game();

  virtual void Run();

private:
  int fps_{60};
  std::string game_title_;
};

}; // namespace game

#endif