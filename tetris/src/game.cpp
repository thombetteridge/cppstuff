#include "game.hpp"
#include "blocks.cpp"

Game::Game()
{
  grid          = Grid();
  blocks        = getAllBlocks();
  current_block = getRandomBlock();
  next_block    = getRandomBlock();
  game_over     = false;
}

auto Game::getRandomBlock() -> Block
{
  if (blocks.empty())
  {
    blocks = getAllBlocks();
  }
  auto index = GetRandomValue(0, static_cast<int>(blocks.size()) - 1);
  auto block = blocks[index];
  blocks.erase(blocks.begin() + index);
  return block;
}

auto Game::getAllBlocks() -> std::vector<Block>
{
  return {
    TBlock(), IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), ZBlock()
  };
}

void Game::draw()
{
  grid.draw();
  current_block.draw(1, 1);
}

void Game::handleInput()
{
  int key_pressed = GetKeyPressed();

  switch (key_pressed)
  {
    case KEY_LEFT:
      moveBlockLeft();
      break;
    case KEY_RIGHT:
      moveBlockRight();
      break;
    case KEY_DOWN:
      moveBlockDown();
      break;
    case KEY_UP:
      rotateBlock();
      break;
    default:
      break;
  }
}

void Game::moveBlockLeft()
{
  if (!game_over)
  {
    current_block.move(0, -1);
    if (isBlockOutside() || blockFits() == false)
    {
      current_block.move(0, 1);
    }
  }
}

void Game::moveBlockRight()
{
  if (!game_over)
  {
    current_block.move(0, 1);
    if (isBlockOutside() || blockFits() == false)
    {
      current_block.move(0, -1);
    }
  }
}

void Game::moveBlockDown()
{
  if (!game_over)
  {
    current_block.move(1, 0);
    if (isBlockOutside() || blockFits() == false)
    {
      current_block.move(-1, 0);
      lockBlock();
    }
  }
}

void Game::rotateBlock()
{
  if (!game_over)
  {
    current_block.rotate();
  }
  if (isBlockOutside() || blockFits() == false)
  {
    current_block.undoRotate();
  }
}

auto Game::isBlockOutside() -> bool
{
  auto tiles = current_block.getCellPosition();
  for (const auto& item : tiles)
  {
    if (grid.isCellOutside(item.row, item.column))
    {
      return true;
    }
  }
  return false;
}

void Game::lockBlock()
{
  auto tiles = current_block.getCellPosition();
  for (const auto& item : tiles)
  {
    grid.grid[item.row][item.column] = current_block.id;
  }
  current_block = next_block;
  if (blockFits() == false)
  {
    game_over = true;
  }
  next_block = getRandomBlock();
  grid.clearFullRoads();
}

auto Game::blockFits() -> bool
{
  auto tiles = current_block.getCellPosition();
  for (const auto& item : tiles)
  {
    if (grid.isCellEmpty(item.row, item.column) == false)
    {
      return false;
    }
  }
  return true;
}