#include <raylib-cpp.hpp>

#include "game.hpp"

auto main() -> int
{

    // Initialization
    int screenWidth = 300;
    int screenHeight = 600;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

    SetTargetFPS(60);

    auto game = Game();

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update

        // TODO: Update your variables here

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        game.draw();

        EndDrawing();
    }

    return 0;
}