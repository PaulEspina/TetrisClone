#include "Well.h"

Well::Well()
{
    pos = sf::Vector2f(0, 0);
    wellWidth = 0;
    wellHeight = 0;
    this->extraBlocks = 0;
    trueWellHeight = 0;
    blockSize = 0;
    occupiedHeight = 0;
}

Well::Well(sf::Vector2f pos, sf::Vector2u dimension, unsigned int extraBlocks, unsigned int blockSize)
{
    this->pos = pos;
    wellWidth = dimension.x;
    wellHeight = dimension.y;
    this->extraBlocks = extraBlocks;
    trueWellHeight = dimension.y + extraBlocks;
    this->blockSize = blockSize;
    wellRect.setPosition(pos + sf::Vector2f(0, extraBlocks * blockSize));
    wellRect.setFillColor(sf::Color(50, 50, 50));
    wellRect.setSize(sf::Vector2f(wellWidth * blockSize, wellHeight * blockSize));
    for(unsigned int i = 0; i < trueWellHeight; i++)
    {
        for(unsigned int j = 0; j < wellWidth; j++)
        {
            sf::RectangleShape rs(sf::Vector2f(blockSize, blockSize));
            rs.setPosition(sf::Vector2f(j * blockSize, i * blockSize) + pos);
            rs.setOutlineColor(sf::Color::Black);
            rs.setOutlineThickness(1);
            blockRects.push_back(rs);
        }
    }
    init();
}

void Well::init()
{
    well.clear();
    newWell.clear();
    for(unsigned int i = 0; i < trueWellHeight; i++)
    {
        std::vector<char> row;
        for(unsigned int j = 0; j < wellWidth; j++)
        {
            row.push_back('0');
        }
        well.push_back(row);
    }
    newWell = well;
    occupiedHeight = 0;
}

void Well::update()
{
    for(unsigned int i = 0; i < wellWidth * trueWellHeight; i++)
    {
        switch(well[i / wellWidth][i % wellWidth])
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
    for(unsigned int i = 0; i < trueWellHeight; i++)
    {
        bool flag = false;
        for(unsigned int j = 0; j < wellWidth; j++)
        {
            if(newWell[i][j] != '0' && newWell[i][j])
            {
                occupiedHeight = trueWellHeight - i;
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
    for(unsigned int i = trueWellHeight - occupiedHeight; i < trueWellHeight; i++)
    {
        bool flag = true;
        for(unsigned int j = 0; j < wellWidth; j++)
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
        for(unsigned int x = 0; x < wellWidth; x++)
        {
            newWell[line][x] = '0';
        }
    }

    // Find lines to adjust
    std::stack<unsigned int> linesToAdjust;
    for(unsigned int i = trueWellHeight - occupiedHeight; i < trueWellHeight; i++)
    {
        bool flag = true;
        for(unsigned int j = 0; j < wellWidth; j++)
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
            for(unsigned int j = 0; j < wellWidth; j++)
            {
                newWell[i][j] = newWell[i - 1][j];
            }
        }
    }
    well = newWell;
}

void Well::render(sf::RenderWindow &window)
{
    window.draw(wellRect);
    for(unsigned int i = 0; i < trueWellHeight; i++)
    {
        for(unsigned int j = 0; j < wellWidth; j++)
        {
            if((i < extraBlocks && blockRects[i * wellWidth + j].getFillColor() != sf::Color(50, 50, 50)) || i >= extraBlocks)
            {
                window.draw(blockRects[i * wellWidth + j]);
            }
        }
    }
}

void Well::showCurrentPiece(Tetromino tetromino)
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

void Well::previewDrop(Tetromino tetromino)
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

void Well::placePiece(Tetromino tetromino)
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

void Well::dropCurrentPiece()
{
    placePiece(previewPiece);
}

bool Well::inBounds(Tetromino tetromino)
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
                if((y < 0 || x < 0 || y >= trueWellHeight || x >= wellWidth))
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

void Well::findValidGrid(Tetromino &tetromino)
{
    int intervalX = 0;
    int intervalY = 0;
    bool success = false;
    while(!success && (unsigned int) intervalX < wellWidth)
    {
        intervalY = 0;
        while((unsigned int) intervalY < trueWellHeight)
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