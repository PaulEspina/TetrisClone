#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Block.h"


class Well
{
public:
    Well() = default;

    Well(sf::Vector2f pos)
    {
        rect = sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
        rect.setPosition(pos);
        rect.setFillColor(sf::Color(50, 50, 50));
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(rect);

        for(sf::RectangleShape* rectBlock : rectBlocks)
        {
            window.draw(*rectBlock);
        }
    }

    void addBlock(Block* block)
    {
        rectBlocks.push_back(block->getRect());
    }

    unsigned int getBlockSize()
    {
        return WIDTH / MAX_GRIDX;
    }

private:
    sf::RectangleShape rect;
    std::vector<sf::RectangleShape*> rectBlocks;

    // make sure these constants will result to a square block filling the whole area
    const unsigned int WIDTH = 300;
    const unsigned int HEIGHT = 600;
    const unsigned int MAX_GRIDX = 10;
    const unsigned int MAX_GRIDY = 24;
};