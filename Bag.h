#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "PieceManager.h"


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
	class Slot
	{
	public:
		Slot();
		Slot(sf::Vector2f pos, unsigned int blockSize);
		Slot(sf::Vector2f pos, unsigned int pieceType, unsigned int blockSize);

		void init();
		void update();
		void render(sf::RenderWindow &window);

		void setPieceType(unsigned int pieceType);
	private:
		unsigned int blockSize;
		
		sf::Vector2f pos;
		std::vector<std::vector<char>> blocks;
		std::vector<sf::RectangleShape> blockRects;
		Tetromino piece;
	};
	unsigned int slotSize;
	unsigned int blockSize;

	sf::Vector2f pos;
	sf::Vector2f size;
	PieceManager *pieceMan;
	std::vector<Slot> slots;
	sf::RectangleShape rect;
};

