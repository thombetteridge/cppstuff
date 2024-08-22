#include "grid.hpp"
#include <iostream>

Grid::Grid()
{
  grid = std::vector<std::vector<int>>(num_rows, std::vector<int>(num_cols, 0));
}

void Grid::random_grid()
{
  for (auto& row : grid)
  {
    for (auto& cell : row)
    {
      cell = GetRandomValue(0, 7);
    }
  }
}

void Grid::draw()
{
  for (int row = 0; row < num_rows; row++)
  {
    for (int col = 0; col < num_cols; col++)
    {
      int cell_value = grid[row][col];
      DrawRectangle(col * cell_size + 1,
                    row * cell_size + 1,
                    cell_size - 1,
                    cell_size - 1,
                    Colours[cell_value]);
    }
  }
}

void Grid::print()
{
  for (const auto& row : grid)
  {
    std::cout << "\n";
    for (const auto& cell : row)
    {
      std::cout << cell;
    }
  }
}

auto Grid::isCellOutside(int row, int column) -> bool
{
  if (row >= 0 && row < num_rows && column >= 0 && column < num_cols)
  {
    return false;
  }
  return true;
}

auto Grid::isCellEmpty(int row, int column) -> bool
{
  if (grid[row][column] == 0)
  {
    return true;
  }
  return false;
}

auto Grid::isRowFull(int row) -> bool
{
  for (int column = 0; column < num_cols; column++)
  {
    if (grid[row][column] == 0)
    {
      return false;
    }
  }
  return true;
}

void Grid::clearRow(int row)
{
  for (int column = 0; column < num_cols; column++)
  {
    grid[row][column] = 0;
  }
}

void Grid::moveRowDown(int row, int n)
{
  for (int column = 0; column < num_cols; column++)
  {
    grid[row + n][column] = grid[row][column];
    grid[row][column]     = 0;
  }
}

auto Grid::clearFullRoads() -> int
{
  int completed = 0;
  for (int row = num_rows - 1; row >= 0; --row)
  {
    if (isRowFull(row))
    {
      clearRow(row);
      completed++;
    }
    else if (completed > 0)
    {
      moveRowDown(row, completed);
    }
  }
  return completed;
}
