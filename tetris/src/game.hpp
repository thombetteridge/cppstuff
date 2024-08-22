#pragma once

#include "../include/raylib-cpp.hpp"
#include <vector>

#include "block.hpp"
#include "grid.hpp"

class Game
{
public:
  Grid grid;

  Game();

  auto getRandomBlock() -> Block;
  auto getAllBlocks() -> std::vector<Block>;
  void draw();
  void handleInput();
  void moveBlockLeft();
  void moveBlockRight();
  void moveBlockDown();

  bool game_over;

private:
  auto isBlockOutside() -> bool;
  auto blockFits() -> bool;
  void rotateBlock();
  void lockBlock();

  std::vector<Block> blocks;
  Block              current_block;
  Block              next_block;
};