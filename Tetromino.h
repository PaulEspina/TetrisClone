#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"

class Tetromino
{
public:
    Tetromino() = default;

    Tetromino(Block blocks[], unsigned int numOfBlocks)
    {
        this->blocks = blocks;
        this->numOfBlocks = numOfBlocks;
    }

    void fall()
    {
        for(unsigned int i = 0; i < numOfBlocks; i++)
        {
            blocks[i].setGridPos(sf::Vector2u(blocks[i].getGridPos().x, blocks[i].getGridPos().y + 1));
        }
    }

    void moveLeft()
    {

        for(unsigned int i = 0; i < numOfBlocks; i++)
        {
            blocks[i].setGridPos(sf::Vector2u(blocks[i].getGridPos().x - 1, blocks[i].getGridPos().y));
        }
    }

    void moveRight()
    {
        for(unsigned int i = 0; i < numOfBlocks; i++)
        {
            blocks[i].setGridPos(sf::Vector2u(blocks[i].getGridPos().x + 1, blocks[i].getGridPos().y));
        }
    }

    Block* getBlocks()
    {
        return blocks;
    }

private:
    Block* blocks;
    unsigned int numOfBlocks;
};