#include "game.hpp"
#include "blocks.cpp"

Game::Game()
{
    grid = Grid();
    blocks = getAllBlocks();
    current_block = getRandomBlock();
    next_block = getRandomBlock();
}

auto Game::getRandomBlock() -> Block
{
    if (blocks.empty()) {
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
        TBlock(),
        IBlock(),
        JBlock(),
        LBlock(),
        OBlock(),
        SBlock(),
        ZBlock()
    };
}

void Game::draw()
{
    grid.draw();
    current_block.draw();
}

void Game::handleInput()
{
    int key_pressed = GetKeyPressed();

    switch (key_pressed) {
    case KEY_LEFT:
        break;
    default:
        break;
    }
}
