#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tetromino.h"
#include "Block.h"


class Well
{
public:
    Well() = default;

    Well(sf::Vector2f pos)
    {
        wellRect = sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
        wellRect.setPosition(pos);
        wellRect.setFillColor(sf::Color(50, 50, 50));
        blockDrawer = sf::RectangleShape(sf::Vector2f(getBlockSize(), getBlockSize()));
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(wellRect);

        for(Block* block : blocks)
        {
            blockDrawer.setFillColor(block->getColor());
            blockDrawer.setPosition(translateGrid(block->getGridPos()));
            window.draw(blockDrawer);
        }
    }

    void addTetromino(Tetromino *tetromino)
    {
        Block *tetBlocks = tetromino->getBlocks();
        for(unsigned int i = 0; i < tetromino->getNumOfBlocks(); i++)
        {
            blocks.push_back(&tetBlocks[i]);
        }
    }

    void addBlock(Block* block)
    {
        blocks.push_back(block);
    }

    unsigned int getBlockSize()
    {
        return WIDTH / MAX_GRIDX;
    }

private:
    sf::RectangleShape blockDrawer;
    sf::RectangleShape wellRect;
    std::vector<Block*> blocks;

    // make sure these constants will result to a square block filling the whole area
    const unsigned int WIDTH = 300;
    const unsigned int HEIGHT = 600;
    const unsigned int MAX_GRIDX = 10;
    const unsigned int MAX_GRIDY = 24;

    sf::Vector2f translateGrid(sf::Vector2u gridPos)
    {
        float x = gridPos.x * getBlockSize();
        float y = gridPos.y * getBlockSize();
        return sf::Vector2f(x, y);
    }
};