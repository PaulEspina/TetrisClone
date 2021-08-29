#pragma once

#include <SFML/Graphics.hpp>
#include "Tetromino.h"

class Well
{
public:
    Well()
    {
        for(unsigned int i = 0; i < WELL_HEIGHT; i++)
        {
            std::vector<char> row;
            for(unsigned int j = 0; j < WELL_WIDTH; j++)
            {
                row.push_back('0');
                sf::RectangleShape rs(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                rs.setPosition(sf::Vector2f(j * BLOCK_SIZE, i * BLOCK_SIZE));
                rs.setOutlineColor(sf::Color::Black);
                rs.setOutlineThickness(1);
                wellRects.push_back(rs);

            }
            well.push_back(row);
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
                wellRects[i].setFillColor(sf::Color(51, 51, 255));
                break;
            case '3':
                wellRects[i].setFillColor(sf::Color(255, 187, 51));
                break;
            case '4':
                wellRects[i].setFillColor(sf::Color(255, 255, 51));
                break;
            case '5':
                wellRects[i].setFillColor(sf::Color(255, 51, 85));
                break;
            case '6':
                wellRects[i].setFillColor(sf::Color(51, 255, 51));
                break;
            case '7':
                wellRects[i].setFillColor(sf::Color(255, 51, 255));
                break;
            }
        }
        for(unsigned int i = 0; i < currentPiece.getShape().size(); i++)
        {
            for(unsigned int j = 0; j < currentPiece.getShape()[0].size(); j++)
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
        std::vector<std::vector<char>> shape = currentPiece.getShape();
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
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

    std::vector<std::vector<char>> well;
    std::vector<sf::RectangleShape> wellRects;
    Tetromino currentPiece;
};