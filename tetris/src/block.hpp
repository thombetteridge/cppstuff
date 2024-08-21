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
    void draw();
    void move(int row, int col);
    auto getCellPosition() -> std::vector<Position>;

private:
    int cell_size { 30 };
    int rotation { 0 };
    int row_offset { 0 };
    int col_offset { 0 };
};