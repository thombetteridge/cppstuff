#pragma once

#include "../include/raylib-cpp.hpp"
#include <map>
#include <vector>

static const std::vector<Color> Colours
  = { RAYWHITE, GREEN, RED, ORANGE, YELLOW, PURPLE, SKYBLUE, BLUE };

class Grid
{
public:
  Grid();
  std::vector<std::vector<int>> grid;

  void random_grid();
  void print();
  void draw();
  auto isCellOutside(int row, int column) -> bool;
  auto isCellEmpty(int row, int column) -> bool;
  int  clearFullRoads();

private:
  int num_rows { 20 };
  int num_cols { 10 };
  int cell_size { 30 };

  auto isRowFull(int row) -> bool;
  void clearRow(int row);
  void moveRowDown(int row, int n);
};
