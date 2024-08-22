#pragma once

#include <map>
#include <vector>

#include "grid.hpp"
#include "position.hpp"

#include "../include/raylib-cpp.hpp"

class Block {
public:
    int id;
    std::map<int, std::vector<Position>> cells;
    Block();
    void draw(int offsetX, int offsetY);
    void move(int row, int col);
    auto getCellPosition() -> std::vector<Position>;

private:
    int cell_size;
    int rotation;
    int row_offset;
    int col_offset;
};