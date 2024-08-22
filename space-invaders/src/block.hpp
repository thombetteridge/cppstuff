#pragma once

#include "../include/raylib-cpp.hpp"

class Block {
public:
    Block(Vector2 position);
    void Draw();
    Block();

private:
    Vector2 position;
};