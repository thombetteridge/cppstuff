#include "../include/raylib-cpp.hpp"
#include "game.hpp"
#include <iostream>

auto event_triggered(double interval, double& last_update_time) -> bool
{
  double current_time = GetTime();
  if (current_time - last_update_time >= interval)
  {
    last_update_time = current_time;
    return true;
  }
  return false;
}

auto main() -> int
{
  const int screenWidth  = 500;
  const int screenHeight = 620;

  const double game_speed = 0.2;

  double last_update_time = 0;

  raylib::Window w(screenWidth, screenHeight, "Tetris");

  SetTargetFPS(60);

  auto game = Game();

  // Main game loop
  while (!w.ShouldClose())  // Detect window close button or ESC key
  {
    // Update
    game.handleInput();
    if (event_triggered(game_speed, last_update_time))
    {
      game.moveBlockDown();
    }
    
    auto score_str = std::to_string(game.score);
  
    // Draw
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, GRAY);
    DrawRectangleRounded({ 320, 250, 170, 180 }, 0.3, 6, GRAY);
    raylib::DrawText("Score", 365, 15, 38, RAYWHITE);
    raylib::DrawText(score_str.c_str(), 333, 65, 38, RAYWHITE);
    raylib::DrawText("Next", 370, 175, 38, RAYWHITE);
    if (game.game_over)
    {
      raylib::DrawText("GAME OVER", 320, 450, 38, RAYWHITE);
    }
    game.draw();
    EndDrawing();
  }
  return 0;
}
