#include "game/game.h"

namespace game {

Game::Game(const std::string &window_title) : game_title_(window_title) {}
Game::~Game() { CloseWindow(); }

void Game::Run() {
  InitWindow(kGameWidth, kGameHeight, game_title_.c_str());
  SetTargetFPS(fps_);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Musashi!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }
}

}; // namespace game