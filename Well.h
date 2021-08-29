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
        newWell = well;
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
        well = newWell;
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
        sf::Vector2i gridPos = currentPiece.getGridPos();
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                if(inBounds(gridPos, i, j, shape))
                {
                    well[gridPos.y + i][gridPos.x + j] = shape[i][j];
                }
            }
        }
    }

    void placePiece(Tetromino tetromino)
    {
        std::vector<std::vector<char>> shape = currentPiece.getShape();
        sf::Vector2i gridPos = currentPiece.getGridPos();
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                if(inBounds(gridPos, i, j, shape))
                {
                    newWell[gridPos.y + i][gridPos.x + j] = shape[i][j];
                }
            }
        }
    }

    bool inBounds(Tetromino tetromino)
    {
        std::vector<std::vector<char>> shape = tetromino.getShape();
        sf::Vector2i gridPos = tetromino.getGridPos();
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                if(shape[i][j] != '0' &&
                   (gridPos.y + i < 0 || gridPos.x + j < 0 ||
                   gridPos.y + i >= WELL_HEIGHT || gridPos.x + j >= WELL_WIDTH))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool inBounds(sf::Vector2i gridPos, unsigned int i, unsigned int j, std::vector<std::vector<char>> shape)
    {
        if(shape[i][j] == '0' ||
           gridPos.y + i < 0 || gridPos.x + j < 0 ||
           gridPos.y + i >= WELL_HEIGHT || gridPos.x + j >= WELL_WIDTH)
        {
            return false;
        }
        return true;
    }

    bool inBounds(int y, int x, unsigned int i, unsigned int j, std::vector<std::vector<char>> shape)
    {
        if(shape[i][j] == '0' ||
           y + i < 0 || x + j < 0 ||
           y + i >= WELL_HEIGHT || x + j >= WELL_WIDTH)
        {
            return false;
        }
        return true;
    }

    void findValidGrid(Tetromino &tetromino)
    {
        int intervalX = 1;
        int intervalY = 1;
        bool success = false;
        while(!success)
        {
            if(intervalX < WELL_WIDTH)
            {
                tetromino.move(sf::Vector2i(intervalX, 0));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(-intervalX, 0));
                }
                tetromino.move(sf::Vector2i(-intervalX, 0));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(intervalX, 0));
                }
                intervalX++;
            }
            if(!success && intervalY < WELL_HEIGHT)
            {
                tetromino.move(sf::Vector2i(0, intervalY));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(0, -intervalY));
                }
                tetromino.move(sf::Vector2i(0, -intervalY));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(0, intervalY));
                }
                intervalY++;
            }
        }
    }

private:
    static const int WELL_WIDTH = 10;
    static const int WELL_HEIGHT = 20;
    static const int BLOCK_SIZE = 25;

    std::vector<std::vector<char>> well;
    std::vector<std::vector<char>> newWell;
    std::vector<sf::RectangleShape> wellRects;
    Tetromino currentPiece;
};