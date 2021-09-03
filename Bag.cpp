#include "Bag.h"

// Bag Class

Bag::Bag()
{
    pos = sf::Vector2f(0, 0);
    size = sf::Vector2f(0, 0);
	pieceMan = NULL;
    slotSize = 0;
    blockSize = 0;
}

Bag::Bag(sf::Vector2f pos, PieceManager &pieceMan, unsigned int slotSize, unsigned int blockSize)
{
    this->pos = pos;
    this->size = sf::Vector2f(GRID_WIDTH * blockSize, GRID_HEIGHT * blockSize * slotSize);
	this->pieceMan = &pieceMan;
    this->slotSize = slotSize;
    this->blockSize = blockSize;
    rect.setPosition(pos + sf::Vector2f(0, 0));
    rect.setFillColor(sf::Color(50, 50, 50));
    rect.setSize(size);
}

void Bag::init()
{
    std::deque<int> bag = pieceMan->getBag();
    for(unsigned int i = 0; i < slotSize; i++)
    {
        slots.push_back(PieceBox(pos + sf::Vector2f(0, i * (blockSize * GRID_HEIGHT)), blockSize));
    }
}

void Bag::update()
{
    std::deque<int> bag = pieceMan->getBag();
    for(unsigned int i = 0; i < slots.size(); i++)
    {
        slots[i].setPieceType(bag[i]);
        slots[i].update();
    }
}

void Bag::render(sf::RenderWindow &window)
{
    window.draw(rect);
    for(PieceBox &slot : slots)
    {
        slot.render(window);
    }
}

// PieceBox Class

PieceBox::PieceBox()
{
    pos = sf::Vector2f(0, 0);
    setPieceType(0);
    blockSize = 0;
    init();
}

PieceBox::PieceBox(sf::Vector2f pos, unsigned int blockSize)
{
    this->pos = pos;
    setPieceType(0);
    this->blockSize = blockSize;
    init();
}

PieceBox::PieceBox(sf::Vector2f pos, unsigned int pieceType, unsigned int blockSize)
{
    this->pos = pos;
    setPieceType(pieceType);
    this->blockSize = blockSize;
    init();
}

void PieceBox::init()
{
    blocks.clear();
    blockRects.clear();
    for(unsigned int i = 0; i < GRID_HEIGHT; i++)
    {
        std::vector<char> row;
        for(unsigned int j = 0; j < GRID_WIDTH; j++)
        {
            row.push_back('0');
            sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
            block.setPosition(sf::Vector2f(j * blockSize, i * blockSize) + pos);
            block.setOutlineThickness(1);
            blockRects.push_back(block);
        }
        blocks.push_back(row);
    }
}

void PieceBox::update()
{
    for(unsigned int i = 0; i < blockRects.size(); i++)
    {
        blockRects[i].setOutlineColor(sf::Color::Black);
        switch(blocks[i / GRID_WIDTH][i % GRID_WIDTH])
        {
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
        default:
            blockRects[i].setFillColor(sf::Color(0, 0, 0, 0));
            blockRects[i].setOutlineColor(sf::Color(0, 0, 0, 0));
        }
    }
    //
}

void PieceBox::render(sf::RenderWindow &window)
{
    for(sf::RectangleShape block : blockRects)
    {
        window.draw(block);
    }
}

void PieceBox::setPieceType(unsigned int pieceType)
{
    init();
    piece = Tetromino(pieceType);
    std::vector<std::vector<char>> shape = piece.getShape();
    for(unsigned int i = 0; i < shape.size(); i++)
    {
        for(unsigned int j = 0; j < shape[i].size(); j++)
        {
            blocks[i][j] = shape[i][j];
        }
    }
}
