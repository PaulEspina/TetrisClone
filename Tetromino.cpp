#include "Tetromino.h"

Tetromino::Tetromino()
{
    gridPos = sf::Vector2i(0, 0);
    type = 0;
    atBottom = false;
    dropLock = false;
}

Tetromino::Tetromino(unsigned int type)
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
    atBottom = false;
    dropLock = false;
}

Tetromino::Tetromino(sf::Vector2i gridPos, unsigned int type)
{
    this->gridPos = gridPos;
    this->type = type;
    setType(type);
    atBottom = false;
    dropLock = false;
}

void Tetromino::rotateClockwise()
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

void Tetromino::rotateCounterClockwise()
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

void Tetromino::move(sf::Vector2i distance)
{
    gridPos += distance;
}

void Tetromino::setType(int type)
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

unsigned int Tetromino::getType()
{
    return type;
}

const std::vector<std::vector<char>> Tetromino::getShape()
{
    return shape;
}

void Tetromino::setGridPos(sf::Vector2i gridPos)
{
    this->gridPos = gridPos;
}

sf::Vector2i Tetromino::getGridPos()
{
    return gridPos;
}

bool Tetromino::isAtBottom()
{
    return atBottom;
}

void Tetromino::setAtBottom(bool value)
{
    atBottom = value;
}

bool Tetromino::shouldLock()
{
    return dropLock;
}

void Tetromino::setDropLock(bool value)
{
    dropLock = value;
}
