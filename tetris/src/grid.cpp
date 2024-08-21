#include "grid.hpp"

#include <iostream>

Grid::Grid()
{
    grid = std::vector<std::vector<int>>(num_rows, std::vector<int>(num_cols, 0));
}

void Grid::random_grid()
{
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell = GetRandomValue(0, 7);
        }
    }
}

void Grid::draw()
{
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            int cell_value = grid[row][col];
            DrawRectangle(
                col * cell_size + 1,
                row * cell_size + 1,
                cell_size - 1,
                cell_size - 1,
                Colours[cell_value]);
        }
    }
}

void Grid::print()
{
    for (auto& row : grid) {
        std::cout << "\n";
        for (auto& cell : row) {
            std::cout << cell;
        }
    }
}
