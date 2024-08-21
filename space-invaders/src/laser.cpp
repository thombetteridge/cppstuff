#include "laser.hpp"

Laser::Laser(Vector2 position, int speed)
    : position(position)
    , speed(speed)
    , active(true)
{
}

Laser::~Laser()
{
    // std::cout << "Laser destroyed\n"; 
}

auto Laser::Draw() -> void
{
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, { 243, 216, 63, 255 });
    }
}

auto Laser::Update() -> void
{
    if (active) {
        position.y += speed;
        if (position.y > GetScreenHeight() || position.y < 0) {
            active = false;
        }
    }
}