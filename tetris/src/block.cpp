#include "block.hpp"

Block::Block()
{
    cell_size = 30;
    rotation = 0;
    row_offset = 0;
    col_offset = 0;
}

void Block::draw(int offsetX, int offsetY)
{
    auto tiles = getCellPosition();
    for (auto item : tiles)
    {
        DrawRectangle(item.column * cell_size + offsetX, item.row * cell_size + offsetY, cell_size - 1, cell_size - 1,
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

    for (auto item : tiles)
    {
        auto new_pos = Position(item.row + row_offset, item.column + col_offset);
        moved_tiles.push_back(new_pos);
    }
    return moved_tiles;
}

void Block::rotate()
{
    rotation++;
    if (rotation == static_cast<int>(cells.size()))
    {
        rotation = 0;
    }
}

void Block::undoRotate()
{
    rotation--;
    if (rotation == -1)
    {
        rotation = static_cast<int>(cells.size() - 1);
    }
}