#pragma once

#include <SFML/Graphics.hpp>

class Block
{
public:
    Block() = default;

    Block(sf::Vector2u gridPos, int type)
    {
        this->gridPos = gridPos;
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
            color = sf::Color(51, 51, 255);
            break;
        case 4:
            color = sf::Color(255, 187, 51);
            break;
        case 5:
            color = sf::Color(51, 255, 51);
            break;
        case 6:
            color = sf::Color(255, 51, 85);
            break;
        }
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

private:
    sf::Vector2u gridPos;
    sf::Color color;
};