#include "block.hpp"

Block::Block()
{
  cell_size  = 30;
  rotation   = 0;
  row_offset = 0;
  col_offset = 0;
}

void Block::draw()
{
  auto tiles = getCellPosition();
  for (const auto& item : tiles)
  {
    DrawRectangle(item.column * cell_size + 11,
                  item.row * cell_size + 11,
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

auto Block::getCellPosition() -> std::vector<Position>
{
  std::vector<Position> moved_tiles;
  std::vector<Position> tiles = cells[rotation];
  for (const auto& item : tiles)
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
