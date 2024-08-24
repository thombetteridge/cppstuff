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
  const int screenWidth  = 300;
  const int screenHeight = 600;

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

    // Draw
    BeginDrawing();
    ClearBackground(DARKGRAY);
    game.draw();
    EndDrawing();
  }
  return 0;
}
