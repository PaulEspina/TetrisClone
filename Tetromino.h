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
        type = 0;
    }

    Tetromino(sf::Vector2u gridPos, unsigned int type)
    {
        this->gridPos = gridPos;
        numOfBlocks = 4;
        blocks = new Block[numOfBlocks];
        setType(type);
        update();
    }

    ~Tetromino()
    {
        delete blocks;
    }

    void moveDown()
    {
        gridPos += sf::Vector2u(0, 1);
    }

    void moveUp()
    {
        gridPos += sf::Vector2u(0, -1);
    }

    void moveLeft()
    {
        gridPos += sf::Vector2u(-1, 0);
    }

    void moveRight()
    {
        gridPos += sf::Vector2u(1, 0);
    }

    void update()
    {
        switch(type)
        {
        case 0:
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(2, 0), type);
            blocks[3] = Block(gridPos + sf::Vector2u(3, 0), type);
            break;
        case 1:
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(0, 1), type);
            blocks[3] = Block(gridPos + sf::Vector2u(1, 1), type);
            break;
        case 2:
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(2, 0), type);
            blocks[3] = Block(gridPos + sf::Vector2u(1, 1), type);
            break;
        case 3:
            blocks[0] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 1), type);
            blocks[2] = Block(gridPos + sf::Vector2u(1, 2), type);
            blocks[3] = Block(gridPos + sf::Vector2u(0, 2), type);
            break;
        case 4:
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(0, 1), type);
            blocks[2] = Block(gridPos + sf::Vector2u(0, 2), type);
            blocks[3] = Block(gridPos + sf::Vector2u(1, 2), type);
            break;
        case 5:
            blocks[0] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[1] = Block(gridPos + sf::Vector2u(2, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(1, 1), type);
            blocks[3] = Block(gridPos + sf::Vector2u(0, 1), type);
            break;
        case 6:
            blocks[0] = Block(gridPos, type);
            blocks[1] = Block(gridPos + sf::Vector2u(1, 0), type);
            blocks[2] = Block(gridPos + sf::Vector2u(1, 1), type);
            blocks[3] = Block(gridPos + sf::Vector2u(2, 1), type);
            break;
        }
    }

    void setType(unsigned int type)
    {
        this->type = type;
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
    unsigned int type;
    Block* blocks;
    unsigned int numOfBlocks;
    sf::Vector2u gridPos;
};