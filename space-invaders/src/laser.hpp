#pragma once

#include <raylib-cpp.hpp>

class Laser {
public:
    Laser(Vector2 position, int speed);
    ~Laser();
    void Draw();
    void Update();
    bool active;

private:
    Vector2 position;
    int speed;
};