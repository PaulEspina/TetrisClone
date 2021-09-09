#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "PieceManager.h"

class Bag;
class PieceBox;

const unsigned int GRID_WIDTH = 4;
const unsigned int GRID_HEIGHT = 4;

class Bag
{
public:
	Bag();
	Bag(sf::Vector2f pos, PieceManager &pieceMan, unsigned int slotSize, unsigned int blockSize);

	void init();
	void update();
	void render(sf::RenderWindow &window);

private:
	unsigned int slotSize;
	unsigned int blockSize;

	sf::Vector2f pos;
	sf::Vector2f size;
	PieceManager *pieceMan;
	std::vector<PieceBox> slots;
	sf::RectangleShape rect;
};

class PieceBox
{
public:
	PieceBox();
	PieceBox(sf::Vector2f pos, unsigned int blockSize);
	PieceBox(sf::Vector2f pos, unsigned int pieceType, unsigned int blockSize);

	void init();
	void update();
	void render(sf::RenderWindow &window);

	void setPieceType(unsigned int pieceType);
private:
	void construct(sf::Vector2f pos, unsigned int pieceType, unsigned int blockSize)
	{
		this->pos = pos;
		setPieceType(pieceType);
		this->blockSize = blockSize;
		init();
		for(unsigned int i = 0; i < GRID_HEIGHT; i++)
		{
			for(unsigned int j = 0; j < GRID_WIDTH; j++)
			{
				sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
				block.setPosition(sf::Vector2f(j * blockSize, i * blockSize) + pos);
				block.setOutlineThickness(1);
				blockRects.push_back(block);
			}
		}
	}
	unsigned int blockSize;

	sf::Vector2f pos;
	std::vector<std::vector<char>> blocks;
	std::vector<sf::RectangleShape> blockRects;
	Tetromino piece;
};

