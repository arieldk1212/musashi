#ifndef MUSASHI_INCLUDE_PRAC_RYZE_H_
#define MUSASHI_INCLUDE_PRAC_RYZE_H_

#include "game/game.h"

#include <array>
#include <raylib.h>

constexpr int kGameWidth = 800;
constexpr int kGameHeight = 450;
constexpr unsigned kMaxBuildings = 100;

class Ryze {
public:
  Ryze();

  int spacing{0};
  std::array<Color, kMaxBuildings> build_colors{0};
  std::array<Rectangle, kMaxBuildings> buildings{0};
  Rectangle ryze_player = {400, 280, 40, 40};

  void Run() {
    for (int i{0}; i < kMaxBuildings; ++i) {
      buildings[i].width = static_cast<float>(GetRandomValue(50, 200));
      buildings[i].height = static_cast<float>(GetRandomValue(200, 800));
      buildings[i].y = kGameHeight - 130.0f - buildings[i].height;
      buildings[i].x = -6000.0f + spacing;

      spacing += static_cast<int>(buildings[i].width);

      build_colors[i] =
          Color{static_cast<unsigned char>(GetRandomValue(200, 240)),
                static_cast<unsigned char>(GetRandomValue(200, 240)),
                static_cast<unsigned char>(GetRandomValue(200, 250))};
    }

    Camera2D camera{0};
    camera.target = Vector2{ryze_player.x + 20.0f, ryze_player.y + 20.0f};
    camera.offset = Vector2{kGameWidth / 2.0f, kGameHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(fps_);

    while (!WindowShouldClose()) {
    }
  }

private:
  int fps_{60};
  std::string ryze_title_{"Ryze"};
};

#endif
