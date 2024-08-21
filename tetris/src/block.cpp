#include "block.hpp"

Block::Block()
{
}

void Block::draw()
{
    auto tiles = getCellPosition();
    for (auto& item : tiles) {
        DrawRectangle(item.column * cell_size + 1,
            item.row * cell_size + 1,
            cell_size - 1,
            cell_size - 1,
            Colours[id]);
    }
}

void Block::move(int row, int col)
{
    row_offset += row;
    col_offset += col;
}

std::vector<Position> Block::getCellPosition()
{
    std::vector<Position> tiles = cells[rotation];
    std::vector<Position> moved_tiles;

    for (auto& item : tiles) {
        auto new_pos = Position(item.row + row_offset, item.column + col_offset);
        moved_tiles.push_back(new_pos);
    }
    return moved_tiles;
}
