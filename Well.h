#pragma once

#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include <vector>
#include <stack>

class Well
{
public:
    Well(sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2u dimension = sf::Vector2u(10, 20), unsigned int extraBlocks = 3, unsigned int blockSize = 25)
        :
        WELL_WIDTH(dimension.x),
        WELL_HEIGHT(dimension.y),
        TRUE_WELL_HEIGHT(dimension.y + extraBlocks),
        EXTRA_BLOCK(extraBlocks),
        BLOCK_SIZE(blockSize)
    {
        this->pos = pos;
        wellRect.setPosition(pos + sf::Vector2f(0, EXTRA_BLOCK * BLOCK_SIZE));
        wellRect.setFillColor(sf::Color(50, 50, 50));
        wellRect.setSize(sf::Vector2f(WELL_WIDTH * BLOCK_SIZE, WELL_HEIGHT * BLOCK_SIZE));
        for(unsigned int i = 0; i < TRUE_WELL_HEIGHT; i++)
        {
            for(unsigned int j = 0; j < WELL_WIDTH; j++)
            {
                sf::RectangleShape rs(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                rs.setPosition(sf::Vector2f(j * BLOCK_SIZE, i * BLOCK_SIZE) + pos);
                rs.setOutlineColor(sf::Color::Black);
                rs.setOutlineThickness(1);
                blockRects.push_back(rs);
            }
        }
        init();
    }

    void init()
    {
        well.clear();
        newWell.clear();
        for(unsigned int i = 0; i < TRUE_WELL_HEIGHT; i++)
        {
            std::vector<char> row;
            for(unsigned int j = 0; j < WELL_WIDTH; j++)
            {
                row.push_back('0');
            }
            well.push_back(row);
        }
        newWell = well;
        occupiedHeight = 0;
    }

    void update()
    {
        for(unsigned int i = 0; i < WELL_WIDTH * TRUE_WELL_HEIGHT; i++)
        {
            switch(well[i / WELL_WIDTH][i % WELL_WIDTH])
            {
            case '0':
                blockRects[i].setFillColor(sf::Color(50, 50, 50));
                break;
            case '1':
                blockRects[i].setFillColor(sf::Color(51, 255, 255));
                break;
            case '2':
                blockRects[i].setFillColor(sf::Color(51, 51, 255));
                break;
            case '3':
                blockRects[i].setFillColor(sf::Color(255, 187, 51));
                break;
            case '4':
                blockRects[i].setFillColor(sf::Color(255, 255, 51));
                break;
            case '5':
                blockRects[i].setFillColor(sf::Color(255, 51, 85));
                break;
            case '6':
                blockRects[i].setFillColor(sf::Color(51, 255, 51));
                break;
            case '7':
                blockRects[i].setFillColor(sf::Color(255, 51, 255));
                break;
            case '1' + 10:
                blockRects[i].setFillColor(sf::Color(51, 255, 255, 25));
                break;
            case '2' + 10:
                blockRects[i].setFillColor(sf::Color(51, 51, 255, 25));
                break;
            case '3' + 10:
                blockRects[i].setFillColor(sf::Color(255, 187, 51, 25));
                break;
            case '4' + 10:
                blockRects[i].setFillColor(sf::Color(255, 255, 51, 25));
                break;
            case '5' + 10:
                blockRects[i].setFillColor(sf::Color(255, 51, 85, 25));
                break;
            case '6' + 10:
                blockRects[i].setFillColor(sf::Color(51, 255, 51, 25));
                break;
            case '7' + 10:
                blockRects[i].setFillColor(sf::Color(255, 51, 255, 25));
                break;
            }
        }

        // Find occupied height
        for(unsigned int i = 0; i < TRUE_WELL_HEIGHT; i++)
        {
            bool flag = false;
            for(unsigned int j = 0; j < WELL_WIDTH; j++)
            {
                if(newWell[i][j] != '0' && newWell[i][j])
                {
                    occupiedHeight = TRUE_WELL_HEIGHT - i;
                    flag = true;
                    break;
                }
            }
            if(flag)
            {
                break;
            }
        }

        // Find lines to clear
        std::vector<unsigned int> linesToClear;
        for(unsigned int i = TRUE_WELL_HEIGHT - occupiedHeight; i < TRUE_WELL_HEIGHT; i++)
        {
            bool flag = true;
            for(unsigned int j = 0; j < WELL_WIDTH; j++)
            {
                if(newWell[i][j] == '0')
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                linesToClear.push_back(i);
            }
        }

        //  Clear lines
        for(unsigned int line : linesToClear)
        {
            for(unsigned int x = 0; x < WELL_WIDTH; x++)
            {
                newWell[line][x] = '0';
            }
        }

        // Find lines to adjust
        std::stack<unsigned int> linesToAdjust;
        for(unsigned int i = TRUE_WELL_HEIGHT - occupiedHeight; i < TRUE_WELL_HEIGHT; i++)
        {
            bool flag = true;
            for(unsigned int j = 0; j < WELL_WIDTH; j++)
            {
                if(newWell[i][j] != '0')
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                linesToAdjust.push(i);
            }
        }

        // Adjust lines
        if(!linesToAdjust.empty())
        {
            unsigned int line = linesToAdjust.top();
            linesToAdjust.pop();
            for(unsigned int i = line; i > 0; i--)
            {
                for(unsigned int j = 0; j < WELL_WIDTH; j++)
                {
                    newWell[i][j] = newWell[i - 1][j];
                }
            }
        }
        well = newWell;
    }

    void render(sf::RenderWindow *window)
    {
        window->draw(wellRect);
        /*for(sf::RectangleShape wellRect : blockRects)
        {
            window->draw(wellRect);
        }*/
        for(unsigned int i = 0; i < TRUE_WELL_HEIGHT; i++)
        {
            for(unsigned int j = 0; j < WELL_WIDTH; j++)
            {
                if((i < EXTRA_BLOCK && blockRects[i * WELL_WIDTH + j].getFillColor() != sf::Color(50, 50, 50)) || i >= EXTRA_BLOCK)
                {
                    window->draw(blockRects[i * WELL_WIDTH + j]);
                }
            }
        }
    }

    void showCurrentPiece(Tetromino tetromino)
    {
        currentPiece = tetromino;
        std::vector<std::vector<char>> shape = tetromino.getShape();
        sf::Vector2i gridPos = tetromino.getGridPos();
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                if(shape[i][j] != '0')
                {
                    well[gridPos.y + i][gridPos.x + j] = shape[i][j];
                }
            }
        }
    }

    void previewDrop(Tetromino tetromino)
    {
        while(inBounds(tetromino))
        {
            tetromino.move(sf::Vector2i(0, 1));
        }
        tetromino.move(sf::Vector2i(0, -1));
        previewPiece = tetromino;
        std::vector<std::vector<char>> shape = tetromino.getShape();
        sf::Vector2i gridPos = tetromino.getGridPos();
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                if(shape[i][j] != '0')
                {
                    well[gridPos.y + i][gridPos.x + j] = shape[i][j] + 10;
                }
            }
        }
    }

    void placePiece(Tetromino tetromino)
    {
        if(inBounds(tetromino))
        {
            std::vector<std::vector<char>> shape = tetromino.getShape();
            sf::Vector2i gridPos = tetromino.getGridPos();
            for(unsigned int i = 0; i < shape.size(); i++)
            {
                for(unsigned int j = 0; j < shape[i].size(); j++)
                {
                    if(shape[i][j] != '0')
                    {
                        newWell[gridPos.y + i][gridPos.x + j] = shape[i][j];
                    }
                }
            }
        }
    }

    void dropCurrentPiece()
    {
        placePiece(previewPiece);
    }

    bool inBounds(Tetromino tetromino)
    {
        std::vector<std::vector<char>> shape = tetromino.getShape();
        sf::Vector2i gridPos = tetromino.getGridPos();
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                unsigned int x = gridPos.x + j;
                unsigned int y = gridPos.y + i;
                if(shape[i][j] != '0')
                {
                    if((y < 0 || x < 0 || y >= TRUE_WELL_HEIGHT || x >= WELL_WIDTH))
                    {
                        return false;
                    }
                    else if(newWell[y][x] != '0')
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void findValidGrid(Tetromino &tetromino)
    {
        int intervalX = 0;
        int intervalY = 0;
        bool success = false;
        while(!success && (unsigned int) intervalX < WELL_WIDTH)
        {
            intervalY = 0;
            while((unsigned int) intervalY < TRUE_WELL_HEIGHT)
            {
                tetromino.move(sf::Vector2i(intervalX, intervalY));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(-intervalX, -intervalY));
                }
                tetromino.move(sf::Vector2i(-intervalX, intervalY));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(intervalX, -intervalY));
                }
                tetromino.move(sf::Vector2i(intervalX, -intervalY));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(-intervalX, intervalY));
                }
                tetromino.move(sf::Vector2i(-intervalX, -intervalY));
                if(inBounds(tetromino))
                {
                    success = true;
                    break;
                }
                else
                {
                    tetromino.move(sf::Vector2i(intervalX, intervalY));
                }
                intervalY++;
            }
            intervalX++;
            if(success)
            {
                break;
            }
        }
    }

private:
    const unsigned int EXTRA_BLOCK;
    const unsigned int WELL_WIDTH;
    const unsigned int WELL_HEIGHT;
    const unsigned int TRUE_WELL_HEIGHT;
    const unsigned int BLOCK_SIZE;

    std::vector<std::vector<char>> well;
    std::vector<std::vector<char>> newWell;
    std::vector<sf::RectangleShape> blockRects;
    sf::RectangleShape wellRect;
    sf::Vector2f pos;

    unsigned int occupiedHeight;

    Tetromino currentPiece;
    Tetromino previewPiece;
};