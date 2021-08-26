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

    Tetromino(sf::Vector2u gridPos, unsigned int type)
    {
        this->gridPos = gridPos;
        switch(type)
        {
        case 0:
            numOfBlocks = 4;
            blocks = new Block[numOfBlocks];
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(2, 0), type);
            blocks[3] = Block(gridPos + sf::Vector2u(3, 0), type);
            break;
        case 1:
            numOfBlocks = 4;
            blocks = new Block[numOfBlocks];
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(0, 1), type);
            blocks[3] = Block(gridPos + sf::Vector2u(1, 1), type);
            break;
        case 2:
            numOfBlocks = 4;
            blocks = new Block[numOfBlocks];
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(2, 0), type);
            blocks[3] = Block(gridPos + sf::Vector2u(1, 1), type);
            break;
        case 3:
            numOfBlocks = 4;
            blocks = new Block[numOfBlocks];
            blocks[0] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 1), type);
            blocks[2] = Block(gridPos + sf::Vector2u(1, 2), type);
            blocks[3] = Block(gridPos + sf::Vector2u(0, 2), type);
            break;
        case 4:
            numOfBlocks = 4;
            blocks = new Block[numOfBlocks];
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(0, 1), type);
            blocks[2] = Block(gridPos + sf::Vector2u(0, 2), type);
            blocks[3] = Block(gridPos + sf::Vector2u(1, 2), type);
            break;
        case 5:
            numOfBlocks = 4;
            blocks = new Block[numOfBlocks];
            blocks[0] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[1] = Block(gridPos + sf::Vector2u(2, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(1, 1), type);
            blocks[3] = Block(gridPos + sf::Vector2u(0, 1), type);
            break;
        case 6:
            numOfBlocks = 4;
            blocks = new Block[numOfBlocks];
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(1, 1), type);
            blocks[3] = Block(gridPos + sf::Vector2u(2, 1), type);
            break;
        default:
            numOfBlocks = 0;
            blocks = new Block[0];
        }
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

    unsigned int getNumOfBlocks()
    {
        return numOfBlocks;
    }

private:
    Block* blocks;
    unsigned int numOfBlocks;
    sf::Vector2u gridPos;
};