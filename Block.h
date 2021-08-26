#pragma once

#include <SFML/Graphics.hpp>

class Block
{
public:
    Block() = default;

    Block(sf::Vector2u gridPos, int type, unsigned int blockSize)
    {
        this->gridPos = gridPos;
        rect = sf::RectangleShape(sf::Vector2f(blockSize, blockSize));
        switch(type)
        {
        case 0:
            color = sf::Color(51, 255, 255);
            break;
        case 1:
            color = sf::Color(255, 255, 51);
            break;
        case 2:
            color = sf::Color(255, 51, 255);
            break;
        case 3:
            color = sf::Color(255, 187, 51);
            break;
        case 4:
            color = sf::Color(51, 255, 51);
            break;
        case 5:
            color = sf::Color(255, 51, 85);
            break;
        }
        this->blockSize = blockSize;
    }

    void update()
    {
        rect.setPosition(translateGrid(gridPos));
        rect.setFillColor(color);
    }

    void setGridPos(sf::Vector2u gridPos)
    {
        this->gridPos = gridPos;
    }

    sf::Vector2u getGridPos()
    {
        return gridPos;
    }

    sf::Color getColor()
    {
        return color;
    }

    sf::RectangleShape* getRect()
    {
        return &rect;
    }

private:
    sf::RectangleShape rect;
    sf::Vector2u gridPos;
    sf::Color color;
    unsigned int blockSize;

    sf::Vector2f translateGrid(sf::Vector2u gridPos)
    {
        float x = gridPos.x * blockSize;
        float y= gridPos.y * blockSize;
        return sf::Vector2f(x, y);
    }
};