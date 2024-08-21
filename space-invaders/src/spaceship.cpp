#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("gfx/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
    last_fired_time = 0.0;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

auto Spaceship::Draw() -> void
{
    DrawTextureV(image, position, WHITE);
}

auto Spaceship::MoveLeft() -> void
{
    position.x -= 5;
    if (position.x < 0)
        position.x = 0;
}

auto Spaceship::MoveRight() -> void
{
    position.x += 5;
    if (position.x > GetScreenWidth() - image.width) {
        position.x = GetScreenWidth() - image.width;
    }
}

void Spaceship::FireLaser()
{
    if (GetTime() - last_fired_time >= 0.35) {
        lasers.push_back(Laser({ position.x + (image.width / 2) - 2, position.y }, -6));
        last_fired_time = GetTime();
    }
}
