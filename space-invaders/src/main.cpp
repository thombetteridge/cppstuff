#include "../include/raylib-cpp.hpp"

#include "game.hpp"

int main() {
    
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    raylib::Window w(screenWidth, screenHeight, "Space Invaders");
    
    SetTargetFPS(60);

    Game game;

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update

        game.HandleInput();
        game.Update();
        
        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        game.Draw();

        EndDrawing();
    }

    return 0;
}