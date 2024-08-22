#pragma once

#include "obstacle.hpp"
#include "spaceship.hpp"

#include <vector>

class Game {
public:
    Game();
    ~Game();

    void Draw();
    void Update();
    void HandleInput();

private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
};