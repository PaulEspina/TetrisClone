#pragma once

#include <SFML/Graphics.hpp>
#include "Tetromino.h"

class Well
{
public:
    Well()
    {
        for(int i = 0; i < WELL_WIDTH * WELL_HEIGHT; i++)
        {
            unsigned int gridX = i % WELL_WIDTH;
            unsigned int gridY = i / WELL_WIDTH;
            well[gridY][gridX] = '0';
            wellRects[i] = sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            wellRects[i].setPosition(sf::Vector2f(gridX * BLOCK_SIZE, gridY * BLOCK_SIZE));
            wellRects[i].setOutlineColor(sf::Color::Black);
            wellRects[i].setOutlineThickness(1);
        }
    }

    void update()
    {
        for(int i = 0; i < WELL_WIDTH * WELL_HEIGHT; i++)
        {
            switch(well[i / WELL_WIDTH][i % WELL_WIDTH])
            {
            case '0':
                wellRects[i].setFillColor(sf::Color(50, 50, 50));
                break;
            case '1':
                wellRects[i].setFillColor(sf::Color(51, 255, 255));
                break;
            case '2':
                wellRects[i].setFillColor(sf::Color(255, 255, 51));
                break;
            case '3':
                wellRects[i].setFillColor(sf::Color(255, 51, 255));
                break;
            case '4':
                wellRects[i].setFillColor(sf::Color(51, 51, 255));
                break;
            case '5':
                wellRects[i].setFillColor(sf::Color(255, 187, 51));
                break;
            case '6':
                wellRects[i].setFillColor(sf::Color(51, 255, 51));
                break;
            case '7':
                wellRects[i].setFillColor(sf::Color(255, 51, 85));
                break;
            }
        }
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(currentPiece.getGridPos().y + i >= 0 && currentPiece.getGridPos().x + j >= 0)
                {
                    well[currentPiece.getGridPos().y + i][currentPiece.getGridPos().x + j] = '0';
                }
            }
        }
    }

    void render(sf::RenderWindow *window)
    {
        for(sf::RectangleShape wellRect : wellRects)
        {
            window->draw(wellRect);
        }
    }

    void showCurrentPiece(Tetromino currentPiece)
    {
        this->currentPiece = currentPiece;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                char shape[4][4];
                currentPiece.getShape(shape);
                if(shape[i][j] != '0')
                {
                    well[currentPiece.getGridPos().y + i][currentPiece.getGridPos().x + j] = shape[i][j];
                }
            }
        }
    }

private:
    static const int WELL_WIDTH = 10;
    static const int WELL_HEIGHT = 20;
    static const int BLOCK_SIZE = 25;

    char well[WELL_HEIGHT][WELL_WIDTH];
    sf::RectangleShape wellRects[WELL_WIDTH * WELL_HEIGHT];
    Tetromino currentPiece;
};