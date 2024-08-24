#pragma once

#include "../include/raylib-cpp.hpp"
#include "grid.hpp"
#include "position.hpp"
#include <map>
#include <vector>

class Block
{
public:
  int                                  id;
  std::map<int, std::vector<Position>> cells;

  Block();
  void draw();
  void move(int row, int col);
  auto getCellPosition() -> std::vector<Position>;
  void rotate();
  void undoRotate();

private:
  int cell_size;
  int rotation;
  int row_offset;
  int col_offset;
};
