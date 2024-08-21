#include "game.hpp"

Game::Game()
{
    obstacles = CreateObstacles();
}

Game::~Game()
{
}

auto Game::Draw() -> void
{
    spaceship.Draw();

    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }
    for (auto& obs : obstacles) {
        obs.Draw();
    }
    
}

auto Game::Update() -> void
{

    for (auto& laser : spaceship.lasers) {
        laser.Update();
    }
    DeleteInactiveLasers();
}

auto Game::HandleInput() -> void
{

    if (IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    }
    if (IsKeyDown(KEY_SPACE)) {
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->active) {
            it = spaceship.lasers.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacle_width = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacle_width)) / 5;

    for (int i = 0; i < 4; i++) {
        float offset_x = (i + 1 ) * gap + i * obstacle_width;
        obstacles.push_back(Obstacle({offset_x, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}
