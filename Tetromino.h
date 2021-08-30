#pragma once

#include <string>
#include <SFML/System.hpp>
#include <vector>

class Tetromino
{
public:
    Tetromino()
    {
        gridPos = sf::Vector2i(0, 0);
        type = 0;
    }

    Tetromino(unsigned int type)
    {
        if(type == 4)
        {
            this->gridPos = sf::Vector2i(4, 0);
        }
        else
        {
            this->gridPos = sf::Vector2i(3, 0);
        }
        this->type = type;
        setType(type);
    }

    Tetromino(sf::Vector2i gridPos, unsigned int type)
    {
        this->gridPos = gridPos;
        this->type = type;
        setType(type);
    }

    void rotateClockwise()
    {
        std::vector<std::vector<char>> newShape(shape);
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                newShape[i][j] = shape[shape.size() - 1 - j][i];
            }
        }
        shape = newShape;
    }

    void rotateCounterClockwise()
    {
        std::vector<std::vector<char>> newShape(shape);
        for(unsigned int i = 0; i < shape.size(); i++)
        {
            for(unsigned int j = 0; j < shape[i].size(); j++)
            {
                newShape[i][j] = shape[j][shape.size() - 1 - i];
            }
        }
        shape = newShape;
    }

    void move(sf::Vector2i distance)
    {
        gridPos += distance;
    }

    void setType(int type)
    {
        std::vector<std::vector<char>> temp;
        int dimension = 3;
        if(type == 1)
        {
            dimension = 4;
        }
        if(type == 4)
        {
            dimension = 2;
        }
        for(int i = 0; i < dimension; i++)
        {
            std::vector<char> row;
            for(int j = 0; j < dimension; j++)
            {
                row.push_back('0');
            }
            temp.push_back(row);
        }
        switch(type)
        {
        case 1:
            temp[1][0] = '1';
            temp[1][1] = '1';
            temp[1][2] = '1';
            temp[1][3] = '1';
            break;
        case 2:
            temp[0][0] = '2';
            temp[1][0] = '2';
            temp[1][1] = '2';
            temp[1][2] = '2';
            break;
        case 3:
            temp[0][2] = '3';
            temp[1][0] = '3';
            temp[1][1] = '3';
            temp[1][2] = '3';
            break;
        case 4:
            temp[0][0] = '4';
            temp[0][1] = '4';
            temp[1][0] = '4';
            temp[1][1] = '4';
            break;
        case 5:
            temp[0][0] = '5';
            temp[0][1] = '5';
            temp[1][1] = '5';
            temp[1][2] = '5';
            break;
        case 6:
            temp[0][1] = '6';
            temp[0][2] = '6';
            temp[1][0] = '6';
            temp[1][1] = '6';
            break;
        case 7:
            temp[0][1] = '7';
            temp[1][0] = '7';
            temp[1][1] = '7';
            temp[1][2] = '7';
            break;
        }
        shape = temp;
        this->type = type;
    }

    unsigned int getType()
    {
        return type;
    }

    std::vector<std::vector<char>> getShape()
    {
        return shape;
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
    std::vector<std::vector<char>> shape;
    unsigned int type;
    sf::Vector2i gridPos;
};