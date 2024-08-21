#include "block.hpp"

Block::Block(Vector2 position)
    : position(position)
{
}

auto Block::Draw() -> void
{
    DrawRectangleV(position, { 3, 3 }, { 243, 216, 63, 255 });
}

Block::Block()
{
}
