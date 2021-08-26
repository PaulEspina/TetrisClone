#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <array>

class Tetromino
{
public:
    Tetromino() = default;

    Tetromino(sf::Vector2i gridPos, unsigned int type, unsigned int rotation)
    {
        this->gridPos = gridPos;
        this->type = type;
        this->rotation = rotation;

        for(unsigned int i = 0; i < 4; i++)
        {
            for(unsigned int j = 0; j < 4; j++)
            {
                shape[i][j] = '0';
            }
        }

        switch(type)
        {
        case 1:
            shape[1][0] = '1';
            shape[1][1] = '1';
            shape[1][2] = '1';
            shape[1][3] = '1';
            break;
        case 2:
            shape[0][0] = '2';
            shape[1][0] = '2';
            shape[1][1] = '2';
            shape[1][2] = '2';
            break;
        case 3:
            shape[0][2] = '3';
            shape[1][0] = '3';
            shape[1][1] = '3';
            shape[1][2] = '3';
            break;
        case 4:
            shape[0][1] = '4';
            shape[0][2] = '4';
            shape[1][1] = '4';
            shape[1][2] = '4';
            break;
        case 5:
            shape[0][1] = '5';
            shape[0][2] = '5';
            shape[1][0] = '5';
            shape[1][1] = '5';
            break;
        case 6:
            shape[0][0] = '6';
            shape[0][1] = '6';
            shape[1][1] = '6';
            shape[1][2] = '6';
            break;
        case 7:
            shape[0][1] = '7';
            shape[1][0] = '7';
            shape[1][1] = '7';
            shape[1][2] = '7';
            break;
        }
    }

    void getShape(char shape[4][4])
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                shape[i][j] = this->shape[i][j];
            }
        }
    }

    void move(sf::Vector2i distance)
    {
        gridPos += distance;
    }

    void setGridPos(sf::Vector2i gridPos)
    {
        this->gridPos = gridPos;
    }

    sf::Vector2i getGridPos()
    {
        return gridPos;
    }

private:
    char shape[4][4];
    unsigned int type;
    unsigned int rotation;
    sf::Vector2i gridPos;
};