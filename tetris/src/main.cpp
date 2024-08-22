#include "../include/raylib-cpp.hpp"

#include "game.hpp"

#include <iostream>

double last_update_time = 0;

bool event_triggered(double interval)
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

    // Initialization
    int screenWidth = 300;
    int screenHeight = 600;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

    SetTargetFPS(60);

    auto game = Game();

    std::cout << "hello";

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        game.handleInput();
        if (event_triggered(0.2))
        {
            game.moveBlockDown();
        }

        // TODO: Update your variables here

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        game.draw();

        EndDrawing();
    }

    return 0;
}